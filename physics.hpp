#pragma once

#include <iostream>
#include <cmath>
#include <vector>

class Vec {
    public:
        double x,y;
        Vec(double x, double y): x{x}, y{y} {}
        
        double mag() {
            return sqrt(x*x + y*y);
        }

        friend Vec operator+(const Vec& u, const Vec& v) {
            return Vec(u.x + v.x, u.y + v.y);
        }
        friend Vec operator-(const Vec& u, const Vec& v) {
            return Vec(u.x - v.x, u.y - v.y);
        }

        friend Vec operator*(const double a, const Vec& v) {
            return Vec(v.x*a, v.y*a);
        }
        friend Vec operator*(const Vec& v, const double a) {
            return Vec(v.x*a, v.y*a);
        }
        
        Vec operator=(const Vec& v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vec operator+=(const Vec& v) {
            *this = *this + v;
            return *this;
        }
        Vec operator*=(const double a) {
            *this = *this * a;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const Vec& obj) {

            return os << "<"<<obj.x<<","<<obj.y<<">";
        }
 

};

class Particle {
public:
    Vec x, v;
    double m, density, pressure;
    Particle(Vec x): x{x}, v{0,0}, m{1} {}
};

class Physics {
public:

    Vec box_size;
    double fluid_density = 1;
    double smoothing_radius = 1;


    std::vector<Particle> particles;
    Physics(int num_of_particles);
    double W(Vec xi, Vec xj, double r);
    Vec grad_W(Vec xi, Vec xj);

    double density(Particle i);
    double pressure(Particle i);
    Vec pressure_force(Particle i);
    void step();

    void apply_force(Particle &p, Vec f);
    void move(Particle &p);

    void resolve_wall_collision(Particle &p) {
        double velocity_loss = 0.5;

        if (abs(p.x.x) > box_size.x/2) {
            p.x.x = box_size.x/2 * p.x.x/abs(p.x.x);
            p.v.x *= -1 * velocity_loss;
        }
        if (abs(p.x.y) > box_size.y/2) {
            p.x.y = box_size.y/2 * p.x.y/abs(p.x.y);
            p.v.y *= -1 * velocity_loss;
        }
    }
};
