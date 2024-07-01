#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "geometry.hpp"


class Physics {

    Box box;
    double volume;
    std::vector<Particle> particles;
    double W(Vec x);
    Vec grad_W(Vec x);

    double density(Particle i);
    double pressure(Particle i);
    Vec pressure_force(Particle i);

    void apply_force(Particle &p, Vec f);
    void move(Particle &p);

    void retraction_force(Particle & p);

    void resolve_wall_collision(Particle &p);
public:

    double propulsion_scalar = 0;
    Vec propulsion_position = Vec(0,0);
    Vec gravity_f = Vec(0,-1);

    double fluid_density;
    double pressure_multiplier;
    double smoothing_radius;

    Physics(int num_of_particles, double rho, double k, double h);
    std::vector<Particle> get_particles();
    Box get_box();
    void step();
};
