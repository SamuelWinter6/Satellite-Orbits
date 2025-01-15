import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Load the orbit data from the `data/` folder
data = pd.read_csv("../data/orbit_2d.csv")

# Extract data
time = data["time(s)"]
x = data["x"]
y = data["y"]

# Calculate distances from the origin
distances = np.sqrt(x**2 + y**2)

# Find periapsis and apogee
periapsis = distances.min()
apogee = distances.max()

# Plot the orbit
plt.figure(figsize=(8, 8))
plt.plot(x, y, label="Orbit Path")

# Add Earth's representation as a circle
earth_radius = 6378
earth = plt.Circle((0, 0), earth_radius, color="blue", alpha=0.3, label="Earth (Radius)")
plt.gca().add_artist(earth)

# Add the Earth's center as a single point
plt.scatter(0, 0, color="blue", label="Planet Center")  # Represent the planet center

# Mark periapsis and apogee
periapsis_idx = np.argmin(distances)
apogee_idx = np.argmax(distances)
plt.scatter(x[periapsis_idx], y[periapsis_idx], color="red", label="Periapsis (Closest Point)")
plt.scatter(x[apogee_idx], y[apogee_idx], color="green", label="Apogee (Farthest Point)")

# Annotate periapsis and apogee
plt.annotate(f"Periapsis: {periapsis:.2f} km", 
             (x[periapsis_idx], y[periapsis_idx]),
             textcoords="offset points", xytext=(-40, 10), ha="center", color="red")
plt.annotate(f"Apogee: {apogee:.2f} km", 
             (x[apogee_idx], y[apogee_idx]),
             textcoords="offset points", xytext=(-40, -20), ha="center", color="green")

# Title and labels
plt.title("2D Satellite Orbit")
plt.xlabel("X Position (km)")
plt.ylabel("Y Position (km)")

# Add gridlines, legend, and axes
plt.axhline(0, color='gray', linewidth=0.5)
plt.axvline(0, color='gray', linewidth=0.5)
plt.legend(loc="lower left")
plt.grid()
plt.axis("equal")
plt.show()