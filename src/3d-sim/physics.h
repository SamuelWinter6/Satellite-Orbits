#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct {
    double mass;              // Mass of the satellite (kg)
    double position[3];       // Position (km)
    double velocity[3];       // Velocity (km/s)
    double fuel_mass;         // Fuel mass (kg)
    double thrust;            // Thrust magnitude (kN)
    double thrust_direction[3]; // Thrust direction (unit vector)
} Satellite;

typedef struct {
    double mass;              // Mass of the planet (kg)
    double position[3];       // Position (km)
    double radius;            // Radius (km)
} Planet;

// Function declarations
void set_thrust_direction(Satellite *sat, double x, double y, double z);
void update_position(Satellite *sat, Planet *planet, double timestep);

#endif
