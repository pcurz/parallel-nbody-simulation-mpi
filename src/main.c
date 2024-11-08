#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "body.h"
#include "file_io.h"
#include "timer.h"

/**
 * @brief Main function to initialize MPI, distribute bodies, calculate forces, update positions,
 *        and gather results.
 * 
 * @param argc Argument count.
 * @param argv Argument values: [<power_of_2_for_bodies>, <initial_data_file>, <output_data_file>].
 * @return int Program exit status.
 */
int main(int argc, char** argv) {
    int nBodies = (int)pow(2, 12);
    if (argc > 1) nBodies = (int)pow(2, atoi(argv[1]));

    const char* initialized_values = (nBodies == 4096) ? "data/initialized_4096" : "data/initialized_65536";
    const char* solution_values = (nBodies == 4096) ? "results/solution_4096_parallel.txt" : "results/solution_65536_parallel.txt";

    if (argc > 2) initialized_values = argv[2];
    if (argc > 3) solution_values = argv[3];

    const float dt = 0.01f;        // Time step for simulation
    const int nIters = 10;         // Number of simulation iterations
    int bytes = nBodies * sizeof(Body); // Total bytes to allocate

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype MPI_Body;
    MPI_Type_contiguous(6, MPI_FLOAT, &MPI_Body);
    MPI_Type_commit(&MPI_Body);

    int* counts = malloc(size * sizeof(int)); // Bodies count per process
    int* offsets = malloc(size * sizeof(int)); // Offsets for each process
    int quotient = nBodies / size;
    int remainder = nBodies % size;

    for (int i = 0; i < size; i++) {
        counts[i] = quotient + (i < remainder ? 1 : 0);
        offsets[i] = (i == 0) ? 0 : offsets[i - 1] + counts[i - 1];
    }

    int local_nBodies = counts[rank];
    Body* local_bodies = (Body*)malloc(local_nBodies * sizeof(Body));
    Body* bodies = (Body*)malloc(nBodies * sizeof(Body));

    if (rank == 0) read_values_from_file(initialized_values, (float*)bodies, bytes);
    MPI_Bcast(bodies, nBodies, MPI_Body, 0, MPI_COMM_WORLD);

    memcpy(local_bodies, &bodies[offsets[rank]], local_nBodies * sizeof(Body));

    double totalTime = 0.0;
    for (int iter = 0; iter < nIters; iter++) {
        StartTimer();

        bodyForce(bodies, local_bodies, nBodies, local_nBodies, dt);

        for (int i = 0; i < local_nBodies; i++) {
            local_bodies[i].x += local_bodies[i].vx * dt;
            local_bodies[i].y += local_bodies[i].vy * dt;
            local_bodies[i].z += local_bodies[i].vz * dt;
        }

        MPI_Allgatherv(local_bodies, local_nBodies, MPI_Body,
                       bodies, counts, offsets, MPI_Body, MPI_COMM_WORLD);

        const double tElapsed = GetTimer() / 1000.0;
        totalTime += tElapsed;

        if (rank == 0) printf("Iteration %d: Execution time = %f seconds\n", iter + 1, tElapsed);
    }

    if (rank == 0) {
        double avgTime = totalTime / (double)(nIters);
        float billionsOfOpsPerSecond = 1e-9 * nBodies * nBodies / avgTime;
        write_valuesText_to_file(solution_values, (float*)bodies, 6 * nBodies);

        printf("\nTotal execution time: %f seconds\n", totalTime);
        printf("Average time per iteration: %f seconds\n", avgTime);
        printf("%0.3f Billion interactions per second\n", billionsOfOpsPerSecond);
    }

    free(local_bodies);
    free(bodies);
    free(counts);
    free(offsets);

    MPI_Type_free(&MPI_Body);
    MPI_Finalize();
    return 0;
}
