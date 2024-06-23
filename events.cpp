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
            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
        }
    }
}
