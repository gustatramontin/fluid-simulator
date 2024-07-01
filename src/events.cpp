#include <SDL2/SDL.h>
#include "events.hpp"

Events::Events() {}

void Events::pool_events() {
    while( SDL_PollEvent(&e) ){

        switch( e.type ){
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_SPACE)
                    pause = !pause;
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                    ext_force = 1;
                else
                    ext_force = -1;
                break;
            case SDL_MOUSEBUTTONUP:
                ext_force = 0;
                break;
            case SDL_MOUSEMOTION:
                mouse_x = e.motion.x;
                mouse_y = e.motion.y;
                break;
            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
        }
    }
}
