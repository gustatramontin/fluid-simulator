# Fluid Simulator
A basic water simulator. In the hamiltonian approach of fluid simulation.
Heavily based on [Particle-based Fluid Simulation](https://cg.informatik.uni-freiburg.de/course_notes/sim_10_sph.pdf) article.
## Run
```
cd python_gui/
python3 main.py
```

## GUI Options
**resume/STOP button**: pause and unpause the simulation

**Show Particles**: show each particle as a pixel

**Show contour**: draws a line around a group of particles

**Fluid Density**: how much compact the particles show be

**Pressure Multiplier**: the strength of the force that pushes particles apart or together

**Smoothin Radius**: the distance at which each particle affect each other

**Gravity Scalar**: the force of gravity
