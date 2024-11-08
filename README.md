# 🌌 Parallel N-Body Simulation with MPI

![C](https://img.shields.io/badge/language-C-blue)
![MPI](https://img.shields.io/badge/MPI-enabled-brightgreen)
![CMake](https://img.shields.io/badge/build-CMake-informational)
![Optimization](https://img.shields.io/badge/optimization-O3-orange)
![License](https://img.shields.io/badge/license-MIT-blue)

**Parallel N-Body Simulation** is a project that simulates the gravitational interactions between celestial bodies in a 3D space using parallel computing with MPI. This approach allows for efficient computation of complex gravitational calculations by distributing the workload across multiple processors.

---

## 📚 Project Overview

In astrophysics, the **N-body problem** involves predicting the motion of celestial bodies interacting through gravitational forces. The complexity of this simulation grows with the number of bodies, making parallel processing essential for handling large datasets.

This project uses **MPI (Message Passing Interface)** to break down these computations, enhancing performance and making the simulation feasible for thousands of interacting bodies.

---

## 📂 Project Structure

```plaintext
parallel-nbody-simulation-mpi/
├── src/
│   ├── main.c             # Main program
│   ├── body.h             # Body struct and force calculation function
│   ├── body.c
│   ├── file_io.c          # Input/output functions
│   ├── file_io.h
│   ├── timer.c            # Timing functions
│   └── timer.h
├── data/                  # Input data files
├── results/               # Output results
└── README.md              # Project documentation
```

---

## 🚀 Features

- **Parallel Computation**: Uses MPI to distribute gravitational calculations across multiple processors.
- **Optimized Performance**: Compiled with `-O3` optimization for maximum speed.
- **Configurable Simulation Size**: Allows adjusting the number of bodies for different performance requirements.

---

## ⚙️ Requirements

- **MPI**: [MPICH](https://www.mpich.org/) or [OpenMPI](https://www.open-mpi.org/).
- **CMake**: A build tool that generates makefiles.
- **C Compiler**: Supports C99 standard.

---

## 🛠️ Building the Project

1. **Create a build directory** and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

2. **Run CMake** to generate makefiles:
   ```bash
   cmake ..
   ```

3. **Compile the project**:
   ```bash
   make
   ```

This will generate an executable named `parallel_nbody`.

---

## 💻 Running the Simulation

Execute the program using `mpirun` with a specified number of processes:

```bash
mpirun -np <num_processes> ./parallel_nbody <power_of_2_for_bodies> <initial_data_file> <output_data_file>
```

- `<num_processes>`: Number of MPI processes (adjust based on available cores).
- `<power_of_2_for_bodies>`: Sets the number of bodies as 2^n (default: 4096).
- `<initial_data_file>`: File with initial body data (in `/data`).
- `<output_data_file>`: File for simulation results (in `/results`).

### Example Command

```bash
mpirun -np 4 ./parallel_nbody 12 data/initialized_4096 results/solution_4096_parallel.txt
```

---

## 📈 Output

- **Result File**: Stores body positions and velocities after each iteration.
- **Performance Metrics**: Execution time per iteration, average time, and billions of interactions per second.

Example output:

```
Total execution time: 0.432 seconds
Average time per iteration: 0.043 seconds
23.456 Billion interactions per second
```

---

## 🧬 Technical Details

1. **Data Distribution**: Bodies are distributed among processes based on the number of available processors.
2. **Force Calculation**: Each process calculates gravitational forces on its assigned bodies.
3. **Position Update**: Local bodies' positions are updated based on the calculated forces.
4. **Synchronization**: Processes synchronize data to ensure consistency across the simulation.
5. **Timing**: Functions track execution time for performance evaluation.

---

## 📂 Example Data Structure

The results are stored in `results/`, containing rows of body positions and velocities.

```plaintext
x y z vx vy vz
x y z vx vy vz
...
```

---

## 🔧 Future Improvements

- **Support for Adaptive Time Steps**: Adjust time steps based on proximity of bodies to improve accuracy.
- **Load Balancing**: Distribute computations more evenly among processors.
- **Visualization**: Add support for visualizing the simulation in real-time.

---

## 🤝 Contributing

Feel free to open issues or submit pull requests to improve the project! Contributions to enhance performance, add features, or fix bugs are always welcome.

---

## 📜 License

This project is licensed under the MIT License. See `LICENSE` for more details.
