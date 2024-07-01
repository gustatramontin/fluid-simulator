
#include "visuals.hpp"

Visuals::Visuals(): width{WIDTH}, height{HEIGHT}, offset_x{0}, offset_y{0} {
	w = SDL_CreateWindow("Fluid Simulator v2", 0,0, width, height, SDL_WINDOW_SHOWN);
        r = SDL_CreateRenderer( w, -1, SDL_RENDERER_ACCELERATED );
}

pixel Visuals::to_pixel(Vec x) {
    int px = floor(x.x) + offset_x;
    int py = -floor(x.y) + offset_y;

    return std::make_pair(px, py);
}
Vec Visuals::to_vec(int px, int py) {
    double x = px - offset_x;
    double y = -(py - offset_y);

    return Vec(x,y);
}

void Visuals::toggle_color(SDL_Color c) {
    rgba = c;
    use_default_color = !use_default_color;
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

void Visuals::draw_line(pixel p1, pixel p2) {
    
    SDL_Color color = rgba;
    if (use_default_color)
        color = {0x00, 0x00, 0xFF, 0xFF};
        

   SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(r, p1.first, p1.second, p2.first, p2.second);
}
void Visuals::draw(Box b) {
    for (auto s : b.get_segments()) {
        draw_line(to_pixel(s.first), to_pixel(s.second));
    }
}

void Visuals::draw_pressure() {

}

Grid Visuals::make_grid(std::vector<Particle> particles) {

    Grid marching_squares_grid;
    std::array<int, WIDTH/GRID_RATIO> zero_row;
    zero_row.fill(0);
    marching_squares_grid.fill(zero_row);

      for (Particle p : particles) {
          pixel pos = to_pixel(p.x);

          marching_squares_grid[G(pos.second)][G(pos.first)] += 1;
      }
    for (auto & row : marching_squares_grid) {
        for (auto & col : row) {
            if (col >= isovalue)
                col = 1;
        }
    }

    return marching_squares_grid;
}

void Visuals::draw_grid() {
    for (int x=0; x<WIDTH/GRID_RATIO; x++) {
        toggle_color({255,255,255,255});
        draw_line(std::make_pair(x*GRID_RATIO,0), std::make_pair(x*GRID_RATIO, HEIGHT));
        toggle_color({255,255,255,50});
    }
    for (int y=0; y<HEIGHT/GRID_RATIO; y++) {
        draw_line(std::make_pair(0,y*GRID_RATIO), std::make_pair(WIDTH, y*GRID_RATIO));
    }
}
void Visuals::draw_contour(std::vector<Particle> particles) {

    Grid g = make_grid(particles);

    for (int r=0; r<g.size()-1; r++) {
        for (int c=0; c<g[0].size()-1; c++) {
            int contour_case = 8*g[r][c] + 4*g[r][c+1] + 2*g[r+1][c+1] + 1*g[r+1][c];

            draw_grid_case(std::make_pair(c*GRID_RATIO,r*GRID_RATIO), contour_case);

        }
    }

}

void Visuals::draw_grid_case(pixel pos, int contour_case) {

    int x = pos.first;
    int y = pos.second;

    int cell_w = GRID_RATIO;
    int cell_h = GRID_RATIO;

    pixel c1,c2,c3,c4;

    c1 = std::make_pair(x+cell_w/2,y);
    c2 = std::make_pair(x+cell_w,y+cell_h/2);
    c3 = std::make_pair(x+cell_w/2,y+cell_h);
    c4 = std::make_pair(x,y+cell_h/2);


    switch (contour_case) {
    case 0:
    case 15:
        break;
    case 1:
    case 14:
            draw_line(c4,c3);
        break;
    case 2:
    case 13:
            draw_line(c3, c2);
        break;
    case 3:
    case 12:
            draw_line(c4, c2);
        break;
    case 4:
    case 11:
            draw_line(c1,c2);
        break;
    case 5:
            draw_line(c4,c1);
            draw_line(c3,c2);
        break;
    case 6:
    case 9:
            draw_line(c1,c3);
        break;
    case 7:
    case 8:
            draw_line(c4,c1);
        break;
    case 10:
            draw_line(c1,c2);
            draw_line(c4,c3);
        break;
    }

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
