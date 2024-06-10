#pragma once

#include <SDL2/SDL.h>
#include "physics.hpp"

typedef std::pair<int,int> pixel;

class Visuals {
    SDL_Window * w;
    SDL_Renderer * r;
    SDL_Event e;

    int width, height;

    double offset_x, offset_y;

    public:
        Visuals(int width, int height);

        std::pair<int, int> to_pixel(Vec x);

        void draw(Particle p);
        void draw_rect(Vec x, Vec s);
        void draw_pressure();
        void draw();

        void show();
        void clear();
        void delay(int ms);

        void set_center(int screen_x, int screen_y);
};
