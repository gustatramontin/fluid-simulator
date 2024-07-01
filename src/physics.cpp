#include "physics.hpp"

Physics::Physics(int num_of_particles, double rho, double k, double h): fluid_density{rho}, pressure_multiplier{k}, smoothing_radius{h} {

    box = Box::square(Vec(0,0), 400);
    double gap = 2;
    int square_size = sqrt(num_of_particles);

    volume = 400*400/2;

    double particle_mass = fluid_density*(volume/num_of_particles);

    for (int x=-square_size/2; x<square_size/2; x++) {
        for (int y=-square_size/2; y<square_size/2; y++) {
            Particle p(Vec(x,y)*gap, particle_mass);

            particles.push_back(p);
        }
    }
}

std::vector<Particle> Physics::get_particles() {return particles;}
Box Physics::get_box() {return box;}

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

    for (Particle &p : particles) {
        
        apply_force(p, gravity_f);
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

        apply_force(p, gravity_f);
        //std::cout << pressuref << std::endl;

        retraction_force(p);


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

void Physics::retraction_force(Particle & p) {
        Vec x = propulsion_position;
        Vec dir = (p.x - x);


        double r = 50;
        if (dir.mag() <= r)
            apply_force(p, propulsion_scalar*(dir/dir.mag())*(r/dir.mag())*5);
}

void Physics::resolve_wall_collision(Particle &p) {
	double velocity_loss = 0.80;
        
        auto ps = box.point_outside_box(p.x);
        if (ps.first) {
            p.x = ps.second;
            p.v = p.v.rotate(M_PI)*velocity_loss;
        }
}
