#!/bin/bash

# Compile the 2D simulation
gcc src/2d-sim/main.c src/2d-sim/physics.c -o satellite_simulation_2d -lm

# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo "Compilation failed for 2D simulation."
    exit 1
fi

# Run the 2D simulation
echo "Running 2D simulation..."
./satellite_simulation_2d

# Check if the simulation ran successfully
if [ $? -ne 0 ]; then
    echo "2D simulation failed to run."
    exit 1
fi

# Visualize the 2D simulation results
echo "Visualizing 2D simulation results..."
cd visualization
python plot_orbit_2d.py
