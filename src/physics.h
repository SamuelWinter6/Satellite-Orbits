#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    double mass;          // Mass of the satellite
    double position[3];   // Position (x, y, z)
    double velocity[3];   // Velocity (vx, vy, vz)
    double fuel_mass;     // Remaining fuel mass
    double thrust;        // Thrust capability
} Satellite;

typedef struct {
    double mass;          // Mass of the planet
    double position[3];   // Position (x, y, z)
    double radius;        // Radius of the planet (km)
} Planet;

void update_position(Satellite *sat, Planet *planet, double timestep);

#endif
