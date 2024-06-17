#include "physics.hpp"
#include "visuals.hpp"


int main() {
    Physics f(20*20);
    Visuals v(500,500);
    v.set_center(500/2, 500/2);

    for (int i=0; i<=100; i++) {
        v.clear();
        f.step();

        v.draw_rect(Vec(1,1)*(500/2)-f.box_size*0.5, f.box_size);
        for (Particle p : f.particles) {
            v.draw(p);
         }

        v.show();
        v.delay(100);
    }

    return 0;
}
