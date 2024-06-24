#include "physics.hpp"
#include "visuals.hpp"
#include "events.hpp"
#include <thread>

struct Config {
    bool pause;
    bool draw_grid;
    bool draw_particle;
    bool draw_contour;


    double fluid_density;
    double pressure_multiplier;
    double smoothing_radius;
};

void simulator(struct Config & config) {

    Physics f(600, config.fluid_density, config.pressure_multiplier, config.smoothing_radius);
    Visuals v;
    Events e;
    v.set_center(500/2, 500/2);

    for (;;) {
        e.pool_events();

        f.fluid_density = config.fluid_density;
        f.pressure_multiplier = config.pressure_multiplier;
        f.smoothing_radius = config.smoothing_radius;

        if (e.quit) break;

        v.clear();
        if (!config.pause )
            f.step();

        if (config.draw_grid)
            v.draw_grid();

        v.draw_rect(Vec(1,1)*(500/2)-f.box_size*0.5, f.box_size);
        for (Particle p : f.particles) {
            if (config.draw_particle)
                v.draw(p);
         }

        if (config.draw_contour)
            v.draw_contour(f.particles, f.smoothing_radius);

        v.show();
        v.delay(10);
    }
}
int main() {
    
    struct Config config = {true, false, true, true, 1, 25.1, 10};
    std::thread th1(simulator, std::ref(config));


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

    

    th1.join();

    return 0;
}
