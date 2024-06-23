#include "physics.hpp"
#include "visuals.hpp"
#include "events.hpp"

int main() {
    Physics f(600);
    Visuals v;
    Events e;
    v.set_center(500/2, 500/2);

    for (int i=0; i<=1000; i++) {
        e.pool_events();

        if (e.quit) break;

        v.clear();
        if (!e.pause)
            f.step();

        //v.draw_grid();
        v.draw_rect(Vec(1,1)*(500/2)-f.box_size*0.5, f.box_size);
        for (Particle p : f.particles) {
            v.draw(p);
         }

        v.draw_contour(f.particles, f.smoothing_radius);

        v.show();
        v.delay(10);
    }

    return 0;
}
