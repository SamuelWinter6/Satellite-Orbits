import plotly.graph_objects as go
import pandas as pd
import numpy as np

# Constants
R_Earth = 6371  # Radius of Earth in kilometers

# Load data
data = pd.read_csv("orbit.csv")

# Calculate eccentricity
# Distances from the center (Earth) to each point in the orbit
distances = np.sqrt(data['x']**2 + data['y']**2 + data['z']**2)

# Semi-major axis (a) and semi-minor axis (b)
semi_major_axis = distances.max()
semi_minor_axis = distances.min()

# Eccentricity (e)
eccentricity = np.sqrt(1 - (semi_minor_axis**2 / semi_major_axis**2))

# Calculate periapsis and apoapsis
periapsis = semi_major_axis * (1 - eccentricity)
apoapsis = semi_major_axis * (1 + eccentricity)

# Print results
print(f"Semi-Major Axis (a): {semi_major_axis:.2f} km")
print(f"Semi-Minor Axis (b): {semi_minor_axis:.2f} km")
print(f"Eccentricity (e): {eccentricity:.6f}")
print(f"Periapsis (closest point): {periapsis:.2f} km")
print(f"Apoapsis (farthest point): {apoapsis:.2f} km")

# Generate Earth's sphere in kilometers
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x = R_Earth * np.outer(np.cos(u), np.sin(v))
y = R_Earth * np.outer(np.sin(u), np.sin(v))
z = R_Earth * np.outer(np.ones(np.size(u)), np.cos(v))

# Create the plot
fig = go.Figure()

# Add orbit path
fig.add_trace(go.Scatter3d(
    x=data['x'], y=data['y'], z=data['z'],
    mode='lines',
    line=dict(color='blue', width=2),
    name='Orbit Path'
))

# Add Earth
fig.add_trace(go.Surface(
    x=x, y=y, z=z,
    colorscale='Blues',
    opacity=0.5,
    name='Earth'
))

# Annotate periapsis and apoapsis
peri_index = np.argmin(distances)
apo_index = np.argmax(distances)
fig.add_trace(go.Scatter3d(
    x=[data['x'][peri_index]], y=[data['y'][peri_index]], z=[data['z'][peri_index]],
    mode='markers',
    marker=dict(color='red', size=5),
    name='Periapsis'
))
fig.add_trace(go.Scatter3d(
    x=[data['x'][apo_index]], y=[data['y'][apo_index]], z=[data['z'][apo_index]],
    mode='markers',
    marker=dict(color='green', size=5),
    name='Apoapsis'
))

# Update layout for accurate scaling and appearance
fig.update_layout(
    scene=dict(
        aspectmode="cube",  # Enforces equal scaling on all axes
        xaxis=dict(title="X Position (km)", range=[-30000, 30000]),
        yaxis=dict(title="Y Position (km)", range=[-30000, 30000]),
        zaxis=dict(title="Z Position (km)", range=[-30000, 30000])
    ),
    title=f"3D Satellite Orbit (e = {eccentricity:.6f})",
)

# Add orbit legend and descriptions
fig.update_layout(
    legend=dict(
        itemsizing='constant',
        title="Legend",
    )
)

# Show the plot
fig.show()
