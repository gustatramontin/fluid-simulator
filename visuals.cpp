
#include "visuals.hpp"

Visuals::Visuals(int width, int height): width{width}, height{height}, offset_x{0}, offset_y{0} {
	w = SDL_CreateWindow("Fluid Simulator v2", 0,0, width, height, SDL_WINDOW_SHOWN);
        r = SDL_CreateRenderer( w, -1, SDL_RENDERER_ACCELERATED );
}

pixel Visuals::to_pixel(Vec x) {
    int px = floor(x.x) + offset_x;
    int py = -floor(x.y) + offset_y;

    return std::make_pair(px, py);
}

void Visuals::draw(Particle p) {
   SDL_SetRenderDrawColor(r, 0, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawPoint(r, to_pixel(p.x).first, to_pixel(p.x).second);
}

void Visuals::draw_rect(Vec x, Vec s) {

    SDL_Rect rect = {x.x, x.y, s.x, s.y};
   SDL_SetRenderDrawColor(r, 0, 255, 114, 0xFF);
    SDL_RenderDrawRect(r, &rect);
}

void Visuals::draw_pressure() {

}

void Visuals::show() {
    SDL_RenderPresent(r);
}
void Visuals::clear() {
   SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);
}

void Visuals::delay(int ms) {
    SDL_Delay(ms);
}

void Visuals::set_center(int screen_x, int screen_y) {
    offset_x = screen_x;
    offset_y = screen_y;
}
