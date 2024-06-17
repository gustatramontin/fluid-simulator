#include "physics.hpp"
#include <cmath>

Physics::Physics(int num_of_particles): box_size{Vec(300,300)} {
    double gap = 10;
    int square_size = sqrt(num_of_particles);
    for (int x=-square_size/2; x<square_size/2; x++) {
        for (int y=-square_size/2; y<square_size/2; y++) {
            Particle p(Vec(x,y)*gap);
            particles.push_back(p);
        }
    }
}

double Physics::W(Vec x) {
    double r = smoothing_radius;
    double a = 5.0/(15.0*M_PI*r*r);
    double dist = (x).mag();

    double q = dist/r;

    if (q >= 0*r && q < 1*r)
        return a*(pow(2-q,3) - 4*pow(1-q,3));
    if (q >= 1*r && q < 2*r)
        return a*pow(2-q,3);
    else return 0;
    
    
}
// Todo: calculate for any r
Vec Physics::grad_W(Vec x) {
    /*double r = smoothing_radius;
    double a = 5.0/(15.0*M_PI*r*r);

    double dist = (xi - xj).mag();
    if (dist == 0) return Vec(0, 0);

    double q = dist/r;

    double res = 0;
    if (q >= 0*r && q < 1*r)
        res = a*(-3*pow(2-q,2) + 12*pow(1-q,2));
    if (q >= 1*r && q < 2*r)
        res = a*-3*pow(2-q,2);

    return -1*((xi-xj)*(1/dist))*res;*/


    double step = 0.001f;
    double dx = W(x + Vec(1,0)*step) - W(x);
    double dy = W(x + Vec(0,1)*step) - W(x);

    Vec grad = Vec(dx,dy)/step;

    return grad;
}


double Physics::density(Particle i) {
    double rho = 0;
    for (Particle p : particles) {
        rho += p.m*W(i.x-p.x);

    }

    return rho;
}

double Physics::pressure(Particle i) {
    double k = 1;
    return k*(pow(i.density/fluid_density, 7) - 1);
}   

Vec Physics::pressure_force(Particle i) {
    Vec f(0,0);
    for (Particle j : particles) {
        f += -j.m*(i.pressure/(i.density*i.density) + j.pressure/(j.density*j.density))*grad_W(i.x-j.x);

        //std::cout << grad_W(i.x, j.x).x << " " << grad_W(i.x, j.x).y << std::endl;
    }

    return f;
}
void Physics::step() {

    for (Particle &p : particles) { 
        p.density = density(p);
        p.pressure = pressure(p);

        //std::cout << p.density << " " <<p.pressure << std::endl;
    }

    for (Particle &p : particles) {
        Vec gravityf = Vec(0,-1);
        Vec pressuref = pressure_force(p);

        apply_force(p, gravityf);
        apply_force(p, pressuref);
        //std::cout << pressuref.x << " " << pressuref.y << std::endl;


        move(p);
        resolve_wall_collision(p);
    }
}

void Physics::apply_force(Particle &p, Vec f) {
    p.v += f;
}

void Physics::move(Particle &p) {
    p.x += p.v;
}
