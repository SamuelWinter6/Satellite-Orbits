#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "physics.h"

#define G 6.67430e-20  // Gravitational constant (km^3/kg/s^2)
#define EXHAUST_VELOCITY 3  // Exhaust velocity in km/s

void update_position(Satellite *sat, Planet *planet, double timestep) {
    // Calculate gravitational force
    double dx = planet->position[0] - sat->position[0];
    double dy = planet->position[1] - sat->position[1];
    double dz = planet->position[2] - sat->position[2];
    double distance = sqrt(dx * dx + dy * dy + dz * dz);

    if (distance < 0.001 * planet->radius) {  // Avoid singularities
        distance = 0.001 * planet->radius;
    }

    double force = (G * sat->mass * planet->mass) / (distance * distance);

    // Calculate acceleration due to gravity
    double ax_gravity = force * dx / (sat->mass * distance);
    double ay_gravity = force * dy / (sat->mass * distance);
    double az_gravity = force * dz / (sat->mass * distance);

    // Calculate thrust acceleration (only if fuel remains)
    double ax_thrust = 0.0, ay_thrust = 0.0, az_thrust = 0.0;
    if (sat->fuel_mass > 0 && sat->thrust > 0) {
        double thrust_magnitude = sat->thrust / sat->mass;  // Thrust per unit mass

        // Calculate thrust direction relative to the spacecraft's velocity
        double direction[3] = {sat->velocity[0], sat->velocity[1], sat->velocity[2]};
        double magnitude = sqrt(direction[0] * direction[0] +
                                direction[1] * direction[1] +
                                direction[2] * direction[2]);

        if (magnitude > 0) {  // Normalize direction vector
            direction[0] /= magnitude;
            direction[1] /= magnitude;
            direction[2] /= magnitude;
        } else {  // Default to a fixed direction if velocity is zero
            direction[0] = 1.0;  // Example thrust along x-axis
            direction[1] = 0.0;
            direction[2] = 0.0;
        }

        ax_thrust = thrust_magnitude * direction[0];
        ay_thrust = thrust_magnitude * direction[1];
        az_thrust = thrust_magnitude * direction[2];

        // Calculate fuel consumption
        double fuel_consumed = (sat->thrust * timestep) / EXHAUST_VELOCITY;
        sat->fuel_mass -= fuel_consumed;
        if (sat->fuel_mass < 0) {
            sat->fuel_mass = 0;  // Prevent negative fuel
            sat->thrust = 0;    // Stop thrust when fuel is depleted
        }
    }

    // Update velocities (gravity + thrust)
    sat->velocity[0] += (ax_gravity + ax_thrust) * timestep;
    sat->velocity[1] += (ay_gravity + ay_thrust) * timestep;
    sat->velocity[2] += (az_gravity + az_thrust) * timestep;

    // Update positions
    sat->position[0] += sat->velocity[0] * timestep;
    sat->position[1] += sat->velocity[1] * timestep;
    sat->position[2] += sat->velocity[2] * timestep;

    // Collision detection
    if (distance < planet->radius) {
        printf("Satellite has collided with the Earth!\n");
        exit(1);  // Stop simulation
    }

    // Debugging output
    printf("Fuel: %.2f, Thrust Acceleration: (%.6e, %.6e, %.6e), Velocity: (%.6e, %.6e, %.6e), Position: (%.6e, %.6e, %.6e)\n",
           sat->fuel_mass, ax_thrust, ay_thrust, az_thrust,
           sat->velocity[0], sat->velocity[1], sat->velocity[2],
           sat->position[0], sat->position[1], sat->position[2]);
}
