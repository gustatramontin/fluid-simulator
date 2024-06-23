#include "physics.hpp"
#include <cmath>

Physics::Physics(int num_of_particles): box_size{Vec(400,400)}, n_particles{num_of_particles} {

    double gap = 11;
    int square_size = sqrt(n_particles);

    volume = box_size.x*box_size.y/2;

    double particle_mass = fluid_density*(volume/n_particles);

    for (int x=-square_size/2; x<square_size/2; x++) {
        for (int y=-square_size/2; y<square_size/2; y++) {
            Particle p(Vec(x,y)*gap, particle_mass);

            particles.push_back(p);
        }
    }
}

double Physics::W(Vec x) {
    double r = smoothing_radius;
    double a = 5.0/(14.0*M_PI*r*r);
    double dist = x.mag();

    double q = dist/r;

    if (q >= 0 && q < 1)
        return a*(pow(2-q,3) - 4*pow(1-q,3));
    if (q >= 1 && q < 2)
        return a*pow(2-q,3);
    if (q >= 2)
        return 0;
    
    
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
    for (Particle j : particles) {
        if ((i.x - j.x).mag() >= 2*smoothing_radius) continue;
        rho += j.m*W(i.x-j.x);
    }

    return rho;
}

double Physics::pressure(Particle i) {
    double k = pressure_multiplier;
    return k*(pow(i.density/fluid_density, 1) - 1);
}   

Vec Physics::pressure_force(Particle i) {
    Vec f(0,0);
    for (Particle j : particles) {
        if ((i.x - j.x).mag() >= 2*smoothing_radius) continue;

        f += j.m*(i.pressure/(i.density*i.density) + j.pressure/(j.density*j.density))*grad_W(i.x - j.x);

    }

    return -1*f;
}
void Physics::step() {
    Vec gravityf = Vec(0,-1.0);

    for (Particle &p : particles) {
        
        apply_force(p, gravityf);
        p.next_x = p.x + p.v;

        p.swap_x();
        p.density = density(p);
        p.pressure = pressure(p);

        //std::cout << p.density << " " <<p.pressure << std::endl;
    }

    for (Particle &p : particles) {
        p.swap_x();
        Vec pressuref = pressure_force(p);

        p.v = pressuref;
        apply_force(p, gravityf);
        //std::cout << pressuref << std::endl;


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

void Physics::resolve_wall_collision(Particle &p) {
	double velocity_loss = 0.80;
        Vec boundary = box_size/2 - Vec(1,1)*2;

        
	if (abs(p.x.x) > boundary.x) {
		p.x.x = boundary.x * (p.x.x/abs(p.x.x));
		p.v.x *= -1 * velocity_loss;
	}
	if (abs(p.x.y) > boundary.y) {
		p.x.y = boundary.y * (p.x.y/abs(p.x.y));
		p.v.y *= -1 * velocity_loss;
	}
}
