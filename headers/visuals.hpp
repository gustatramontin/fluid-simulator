#pragma once

#include <SDL2/SDL.h>
#include <array>
#include "physics.hpp"

#define WIDTH 500
#define HEIGHT 500
#define GRID_RATIO 10

#define G(x) (x)/GRID_RATIO

typedef std::pair<int,int> pixel;

using Grid = std::array<std::array<int, WIDTH/GRID_RATIO>, HEIGHT/GRID_RATIO>;

class Visuals {
    SDL_Window * w;
    SDL_Renderer * r;
    SDL_Event e;
    SDL_Color rgba;
    bool use_default_color = true;


    int width, height;

    double offset_x, offset_y;

    int grid_ratio = 10;
    double isovalue = 1;


    public:
        Visuals();

        std::pair<int, int> to_pixel(Vec x);
        Vec to_vec(int px, int py);

        void toggle_color(SDL_Color c);
        void draw(Particle p);
        void draw_rect(Vec x, Vec s);
        void draw_line(pixel p1, pixel p2);
        void draw(Box b);
        void draw_grid();
        void draw_pressure();
        void draw();

        Grid make_grid(std::vector<Particle> particles);
        void draw_contour(std::vector<Particle> particles);
        void draw_grid_case(pixel pos, int contour_case);

        void show();
        void clear();
        void delay(int ms);

        void set_center(int screen_x, int screen_y);

};
