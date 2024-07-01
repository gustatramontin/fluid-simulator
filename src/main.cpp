#include "physics.hpp"
#include "visuals.hpp"
#include "events.hpp"
#include <thread>

struct Config {
    bool pause;
    bool draw_grid;
    bool draw_particle;
    bool draw_contour;

    bool gravity;
    double gravity_f;

    double fluid_density;
    double pressure_multiplier;
    double smoothing_radius;
};

void simulator(struct Config & config) {

    Physics f(1000, config.fluid_density, config.pressure_multiplier, config.smoothing_radius);
    Visuals v;
    Events e;
    v.set_center(500/2, 500/2);

    for (;;) {
        e.pool_events();

        f.fluid_density = config.fluid_density;
        f.pressure_multiplier = config.pressure_multiplier;
        f.smoothing_radius = config.smoothing_radius;

        f.use_external_force = e.ext_force;
        f.force_dir = e.ext_force_dir;
        f.external_force = v.to_vec(e.mouse_x, e.mouse_y);

        f.enable_gravity = config.gravity;
        f.gravity_f = config.gravity_f;


        if (e.quit) break;

        v.clear();
        if (!config.pause )
            f.step();

        if (config.draw_grid)
            v.draw_grid();


        v.draw(f.box);
        for (Particle p : f.particles) {
            if (config.draw_particle)
                v.draw(p);
         }

        if (config.draw_contour)
            v.draw_contour(f.particles);

        v.show();
        v.delay(10);
    }
}
int main() {
    
    struct Config config = {true, false, true, true, true, 1, 1, 25.1, 10};
    std::thread th1(simulator, std::ref(config));

    th1.detach();

    bool quit = false;
    while (!quit) {
        char c;
        double v;
        std::cin >> c >> v;

        switch (c) {
            case '!':
                config.pause = (bool) (int) v;
                break;
            case 'g':
                config.draw_grid = (int) v;
                break;
            case 'p':
                config.draw_particle = (int) v;
                break;
            case 'c':
                config.draw_contour = (int) v;
                break;
            case 'G':
                config.gravity = (int) v;
                break;
            case 'O':
                config.gravity_f = v;
                break;
            case 'f':
                config.fluid_density = v;
                break;
            case 'k':
                config.pressure_multiplier = v;
                break;
            case 'h':
                config.smoothing_radius = v;
                break;
            case 'q':
                quit = true;
                break;
        }

    }

    return 0;
}
