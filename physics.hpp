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
        friend Vec operator/(const Vec& v, const double a) {
            return Vec(v.x/a, v.y/a);
        }
        friend bool operator==(const Vec & u, const Vec & v) {
            double threshold = 0.001f;
            return abs(u.x - v.x) <= threshold && abs(u.y - v.y) <= threshold;
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
    Vec next_x;
    double m, density, pressure;
    Particle(Vec x, double m): x{x},next_x{x}, v{0,0}, m{m} {}
    void swap_x() {
        Vec old = x;
        x = next_x;
        next_x = old;
    };
};

class Physics {
public:

    Vec box_size;
    double fluid_density = 1;
    double pressure_multiplier = 25.1;
    double smoothing_radius = 10;
    double volume;

    int n_particles;


    std::vector<Particle> particles;
    Physics(int num_of_particles);
    double W(Vec x);
    Vec grad_W(Vec x);

    double density(Particle i);
    double pressure(Particle i);
    Vec pressure_force(Particle i);
    void step();

    void apply_force(Particle &p, Vec f);
    void move(Particle &p);

    void resolve_wall_collision(Particle &p);
};
