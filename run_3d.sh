#!/bin/bash

# Compile the 3D simulation
gcc src/3d-sim/main.c src/3d-sim/physics.c -o satellite_simulation_3d -lm

# Check if compilation succeeded
if [ $? -ne 0 ]; then
    echo "Compilation failed for 3D simulation."
    exit 1
fi

# Run the 3D simulation
echo "Running 3D simulation..."
./satellite_simulation_3d

# Check if the simulation ran successfully
if [ $? -ne 0 ]; then
    echo "3D simulation failed to run."
    exit 1
fi

# Visualize the 3D simulation results
echo "Visualizing 3D simulation results..."
cd visualization
python plot_orbit_3d.py
