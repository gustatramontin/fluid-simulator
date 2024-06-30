#include "geometry.hpp"

Particle::Particle(Vec x, double m): x{x},next_x{x}, v{0,0}, m{m} {}

void Particle::swap_x() {

        Vec old = x;
        x = next_x;
        next_x = old;
}
