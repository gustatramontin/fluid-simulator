#include "geometry.hpp"
#include "physics.hpp"
#include "visuals.hpp"
#include "events.hpp"
#include <thread>

struct VisualsConfig {
    bool pause = true;
    bool draw_grid = false;
    bool draw_particle = true;
    bool draw_contour = true;
};
struct PhysicsConfig {
    Vec gravity_f = Vec(0,-1);

    double fluid_density = 1;
    double pressure_multiplier = 20;
    double smoothing_radius = 15;
};

void simulator(struct PhysicsConfig & physicsConfig, struct VisualsConfig & visualsConfig) {

    Physics f(1000, physicsConfig.fluid_density, physicsConfig.pressure_multiplier, physicsConfig.smoothing_radius);
    Visuals v;
    Events e;
    v.set_center(500/2, 500/2);

    for (;;) {
        e.pool_events();

        f.fluid_density = physicsConfig.fluid_density;
        f.pressure_multiplier = physicsConfig.pressure_multiplier;
        f.smoothing_radius = physicsConfig.smoothing_radius;

        f.propulsion_scalar = e.ext_force;
        f.propulsion_position = v.to_vec(e.mouse_x, e.mouse_y);

        f.gravity_f = physicsConfig.gravity_f;


        if (e.quit) break;

        v.clear();
        if (!visualsConfig.pause )
            f.step();

        if (visualsConfig.draw_grid)
            v.draw_grid();


        v.draw(f.get_box());
        for (Particle p : f.get_particles()) {
            if (visualsConfig.draw_particle)
                v.draw(p);
         }

        if (visualsConfig.draw_contour)
            v.draw_contour(f.get_particles());

        v.show();
        v.delay(10);
    }
}
int main() {
    
    struct PhysicsConfig physicsConfig; 
    struct VisualsConfig visualsConfig; 
    std::thread th1(simulator, std::ref(physicsConfig), std::ref(visualsConfig));

    th1.detach();

    bool quit = false;
    while (!quit) {
        char c;
        double v;
        std::cin >> c >> v;

        switch (c) {
            case '!':
                visualsConfig.pause = (bool) v;
                break;
            case 'g':
                visualsConfig.draw_grid = (bool) v;
                break;
            case 'p':
                visualsConfig.draw_particle = (bool) v;
                break;
            case 'c':
                visualsConfig.draw_contour = (bool) v;
                break;
            case 'G':
                physicsConfig.gravity_f = Vec(0,-1)*v;
                break;
            case 'f':
                physicsConfig.fluid_density = v;
                break;
            case 'k':
                physicsConfig.pressure_multiplier = v;
                break;
            case 'h':
                physicsConfig.smoothing_radius = v;
                break;
            case 'q':
                quit = true;
                break;
        }

    }

    return 0;
}
