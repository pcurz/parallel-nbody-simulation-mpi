#include "body.h"
#include <math.h>

/**
 * @brief Computes the gravitational force on each local body from all other bodies in the system.
 * 
 * @param bodies Array of all bodies in the system.
 * @param local_bodies Array of bodies assigned to the current process.
 * @param nBodies Total number of bodies in the system.
 * @param local_nBodies Number of bodies assigned to the current process.
 * @param dt Time step for updating velocity.
 */
void bodyForce(Body* bodies, Body* local_bodies, int nBodies, int local_nBodies, float dt) {
    for (int i = 0; i < local_nBodies; ++i) {
        float Fx = 0.0f, Fy = 0.0f, Fz = 0.0f;

        for (int j = 0; j < nBodies; j++) {
            float dx = bodies[j].x - local_bodies[i].x;
            float dy = bodies[j].y - local_bodies[i].y;
            float dz = bodies[j].z - local_bodies[i].z;
            float distSqr = dx * dx + dy * dy + dz * dz + SOFTENING;
            float invDist = 1.0f / sqrtf(distSqr);
            float invDist3 = invDist * invDist * invDist;

            Fx += dx * invDist3;
            Fy += dy * invDist3;
            Fz += dz * invDist3;
        }

        local_bodies[i].vx += dt * Fx;
        local_bodies[i].vy += dt * Fy;
        local_bodies[i].vz += dt * Fz;
    }
}
