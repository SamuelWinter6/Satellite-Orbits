#include <stdio.h>
#include <math.h>
#include "physics.h"

int main() {
    // Initialize satellite and planet data
    Satellite sat = {1000, {6671, 0}, {0, 7.73}, 500, 10};  // Mass (kg), Position (km), Velocity (km/s), Fuel Mass (kg), Thrust (kN)
    Planet earth = {5.972e24, {0, 0}, 6371};  // Mass, Position, Radius

    // Initialize thrust direction
    set_thrust_direction(&sat, 0.0, 1.0);  // Initial thrust in the positive y-direction

    double timestep = 1;  // Reduced timestep to 10 seconds
    int steps = 14400;    // Simulate for 4 hours

    // Open a file to store the simulation results
    FILE *file = fopen("data/orbit_2d.csv", "w");  // For 2D
    fprintf(file, "time(s),x,y,vx,vy,fuel_mass\n"); // Telemetry header

    for (int t = 0; t < steps; t++) {
        // Log telemetry data
        fprintf(file, "%d,%.6f,%.6f,%.6f,%.6f,%.2f\n",
                t,
                sat.position[0],  // x in km
                sat.position[1],  // y in km
                sat.velocity[0],  // vx in km/s
                sat.velocity[1],  // vy in km/s
                sat.fuel_mass);   // Fuel mass remains unchanged

        // Update satellite position and velocity
        update_position(&sat, &earth, timestep);
    }

    fclose(file);
    printf("Simulation complete. Data saved to orbit_2d.csv\n");

    return 0;
}
