#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "physics.h"

#define G 6.67430e-20  // Gravitational constant (km^3/kg/s^2)
#define EXHAUST_VELOCITY 3  // Exhaust velocity in km/s

// Function to set thrust direction manually (2D version)
void set_thrust_direction(Satellite *sat, double x, double y) {
    double magnitude = sqrt(x * x + y * y);
    if (magnitude > 0) {
        sat->thrust_direction[0] = x / magnitude;
        sat->thrust_direction[1] = y / magnitude;
    } else {
        sat->thrust_direction[0] = 0.0;
        sat->thrust_direction[1] = 0.0;
    }
}

void update_position(Satellite *sat, Planet *planet, double timestep) {
    // Calculate gravitational force
    double dx = planet->position[0] - sat->position[0];
    double dy = planet->position[1] - sat->position[1];
    double distance = sqrt(dx * dx + dy * dy);

    if (distance < 0.001 * planet->radius) {  // Avoid singularities
        distance = 0.001 * planet->radius;
    }

    double force = (G * sat->mass * planet->mass) / (distance * distance);

    // Calculate acceleration due to gravity
    double ax_gravity = force * dx / (sat->mass * distance);
    double ay_gravity = force * dy / (sat->mass * distance);

    // Calculate thrust acceleration (only if fuel remains)
    double ax_thrust = 0.0, ay_thrust = 0.0;
    if (sat->fuel_mass > 0 && sat->thrust > 0) {
        double thrust_magnitude = sat->thrust / sat->mass;  // Thrust per unit mass

        // Use explicit thrust direction in the global frame
        ax_thrust = thrust_magnitude * sat->thrust_direction[0];
        ay_thrust = thrust_magnitude * sat->thrust_direction[1];

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

    // Update positions
    sat->position[0] += sat->velocity[0] * timestep;
    sat->position[1] += sat->velocity[1] * timestep;

    // Collision detection
    if (distance < planet->radius) {
        printf("Satellite has collided with the Earth!\n");
        exit(1);  // Stop simulation
    }

    // Debugging output
    printf("Fuel: %.2f, Thrust Acceleration: (%.6e, %.6e), Velocity: (%.6e, %.6e), Position: (%.6e, %.6e)\n",
           sat->fuel_mass, ax_thrust, ay_thrust,
           sat->velocity[0], sat->velocity[1],
           sat->position[0], sat->position[1]);
}
