#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "geometry.hpp"


class Physics {
public:

    Vec box_size;
    Vec external_force;
    double force_dir = 1;
    bool use_external_force = false;
    bool enable_gravity = true;

    double gravity_f = 1.0;

    double fluid_density;
    double pressure_multiplier;
    double smoothing_radius;
    double volume;

    int n_particles;


    std::vector<Particle> particles;
    Physics(int num_of_particles, double rho, double k, double h);
    double W(Vec x);
    Vec grad_W(Vec x);

    double density(Particle i);
    double pressure(Particle i);
    Vec pressure_force(Particle i);
    void step();

    void apply_force(Particle &p, Vec f);
    void move(Particle &p);

    void retraction_force(Particle & p, Vec x);

    void resolve_wall_collision(Particle &p);
};
