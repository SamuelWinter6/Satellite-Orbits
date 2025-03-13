# Satellite Orbit Simulation Project

This README provides a summary & step-by-step guide to set up and configure the satellite orbit simulation project. Follow these instructions carefully to ensure the simulation runs.

<!-- SUMMARY_START -->
## **Summary**
This project simulates the motion of a **satellite orbiting a planet (Earth)** in both **2D and 3D** using **Newtonian mechanics**. The simulation calculates the satellite's **trajectory, velocity, and fuel consumption**, while considering the **gravitational force** from the Earth and **thrust acceleration** (if applied).

### **Features**
- Simulates **2D and 3D** orbital motion.
- Uses **Newton’s laws** and **Keplerian mechanics**.
- Implements **thrust control** for maneuvering.
- Performs **collision detection** with the planet.
- Outputs telemetry data to **CSV files** for analysis.

---

## **Mathematical Foundations**
The core physics of the simulation rely on **gravitational dynamics** and **Newton’s laws of motion**.

### **1. Newton’s Law of Universal Gravitation**
The gravitational force exerted by a planet on a satellite is:

\[
F = \frac{G M m}{r^2}
\]

where:
- \( G = 6.67430 \times 10^{-20} \) km³/kg/s² (gravitational constant),
- \( M \) = mass of the planet (Earth: \( 5.972 \times 10^{24} \) kg),
- \( m \) = mass of the satellite,
- \( r \) = distance between the satellite and the planet’s center.

This force is always **attractive** and acts **radially inward** toward the center of the planet.

### **2. Acceleration Due to Gravity**
Using Newton’s second law:

\[
F = m a
\]

Solving for acceleration:

\[
a = \frac{G M}{r^2}
\]

The gravitational acceleration components in **2D** and **3D** are:

\[
a_x = \frac{F}{m} \times \frac{dx}{r}, \quad a_y = \frac{F}{m} \times \frac{dy}{r}
\]

For 3D:

\[
a_x = \frac{F}{m} \times \frac{dx}{r}, \quad a_y = \frac{F}{m} \times \frac{dy}{r}, \quad a_z = \frac{F}{m} \times \frac{dz}{r}
\]

where:
- \( dx, dy, dz \) are the differences in position between the satellite and the planet.

### **3. Orbital Velocity**
For **circular orbits**, the velocity required to maintain orbit is given by:

\[
v = \sqrt{\frac{G M}{r}}
\]

For **elliptical orbits**, Kepler’s third law applies:

\[
T^2 = \frac{4 \pi^2 a^3}{G M}
\]

where \( a \) is the **semi-major axis** and \( T \) is the **orbital period**.

### **4. Thrust Mechanics**
The satellite can change velocity using **thrust acceleration**, computed as:

\[
a_{\text{thrust}} = \frac{T}{m}
\]

where:
- \( T \) = thrust force in kN,
- \( m \) = total mass of the satellite.

The thrust is applied in a user-defined **direction vector**, normalized to unit length:

\[
\hat{t} = \frac{(x, y, z)}{\sqrt{x^2 + y^2 + z^2}}
\]

Fuel consumption follows the **rocket equation**:

\[
\Delta m = \frac{T \cdot \Delta t}{v_{\text{exhaust}}}
\]

where:
- \( v_{\text{exhaust}} \) is the exhaust velocity (3 km/s in this simulation).

### **5. Velocity and Position Updates**
Using **numerical integration (Euler’s Method)**:

\[
v_{\text{new}} = v_{\text{old}} + (a_{\text{gravity}} + a_{\text{thrust}}) \cdot \Delta t
\]

\[
r_{\text{new}} = r_{\text{old}} + v_{\text{new}} \cdot \Delta t
\]

---

This project provides a **functional** and **expandable** satellite simulation using:
- **Newtonian mechanics** for gravity,
- **Thrust dynamics** for maneuvering,
- **Numerical integration** for motion updates.
<!-- SUMMARY_END -->

## Prerequisites

1. **Programming Knowledge:** Basic understanding of C programming language.
2. **System Requirements:**
   - Operating System: Windows/Linux/MacOS
   - Memory: Minimum 4 GB RAM
   - Compiler: GCC or any compatible C compiler: https://sourceforge.net/projects/mingw-w64/?

## Step 1: Clone the Repository

```bash
# Use the following command to clone the repository:
git clone https://github.com/SamuelWinter6/Satellite-Orbits.git

# Navigate to the project directory:
cd Satellite-Orbits
```

## Step 2: Install Dependencies

Ensure the required libraries and tools are installed on your system.

### C Libraries:
- **`math.h`**: For mathematical calculations (e.g., trigonometry, square roots).
- **`stdio.h`**: For input/output operations.
- **`stdlib.h`**: For memory allocation and general utilities.
- **`string.h`**: For string manipulation.

### Python Libraries (for visualization):
- **`plotly`**: For interactive orbit plotting.
  ```bash
  pip install plotly
  ```
- **`pandas`**: For handling simulation data.
  ```bash
  pip install pandas
  ```
- **`numpy`**: For numerical operations and array handling.
  ```bash
  pip install numpy
  ```

### Linux/MacOS:
```bash
sudo apt update
sudo apt install build-essential gcc
```

### Windows:
1. Download and install [MinGW](http://www.mingw.org/).
2. Ensure `gcc` is added to the system's PATH environment variable.

## Step 3: Configure Simulation Parameters

1. Open the configuration file `config.h` using a text editor.
2. Adjust the following parameters as needed:
   - **Simulation Time:** Define the total duration of the simulation.
   - **Initial Conditions:** Set the initial position, velocity, and other parameters of the satellite.
   - **Output Options:** Configure the output format and frequency.

Example:
```c
#define SIMULATION_TIME 3600 // 1 hour
define INITIAL_POSITION {1000.0, 0.0, 0.0} // x, y, z in kilometers
define INITIAL_VELOCITY {0.0, 7.8, 0.0} // x, y, z in km/s
```

## Step 4: Build the Project

Compile the source code using the following command:

```bash
make
```

If `make` is not available, compile manually:

```bash
gcc -o satellite_simulation main.c simulation.c utils.c -lm
```

## Step 5: Run the Simulation

Execute the simulation program:

```bash
./satellite_simulation
```

The output will display the satellite's trajectory and save results to a file if configured.

## Step 6: Visualize Results

1. Ensure Python is installed on your system.
2. Install the required Python libraries:
   ```bash
   pip install plotly pandas numpy
   ```
3. Run the visualization script:
   ```bash
   python visualize_orbit.py
   ```
   This script will generate 2D plots of the satellite's trajectory.

## Troubleshooting

- **Compilation Errors:**
  - Ensure all source files are in the same directory.
  - Verify that your compiler supports the `-lm` flag for the math library.

- **Runtime Errors:**
  - Check the configuration file for incorrect parameters.
  - Ensure sufficient memory is available.

- **Visualization Issues:**
  - Verify Python and required libraries are correctly installed.
  - Check the output data file for completeness.

- **Dependency/Setup Issues**
  - I highly recommend to use chatgpt to navigate through issues and solve them, like when adding gcc to path. As steps are different for Mac/Windows/Linux.

## Contributing

1. Fork the repository.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes and push them to your forked repository:
   ```bash
   git add .
   git commit -m "Description of changes"
   git push origin feature-name
   ```
4. Open a pull request in the original repository.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---