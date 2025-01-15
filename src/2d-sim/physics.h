#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    double mass;              // Mass of the satellite (kg)
    double position[2];       // Position (km) in 2D
    double velocity[2];       // Velocity (km/s) in 2D
    double fuel_mass;         // Fuel mass (kg)
    double thrust;            // Thrust magnitude (kN)
    double thrust_direction[2]; // Thrust direction (unit vector) in 2D
} Satellite;

typedef struct {
    double mass;              // Mass of the planet (kg)
    double position[2];       // Position (km) in 2D
    double radius;            // Radius (km)
} Planet;

// Function declarations
void set_thrust_direction(Satellite *sat, double x, double y);
void update_position(Satellite *sat, Planet *planet, double timestep);

#endif