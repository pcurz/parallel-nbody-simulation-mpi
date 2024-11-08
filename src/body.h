#ifndef BODY_H
#define BODY_H

#define SOFTENING 1e-9f

typedef struct {
    float x, y, z;   // Positions
    float vx, vy, vz; // Velocities
} Body;

void bodyForce(Body* bodies, Body* local_bodies, int nBodies, int local_nBodies, float dt);

#endif // BODY_H
