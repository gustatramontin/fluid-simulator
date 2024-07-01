
class Events {
    SDL_Event e;
public:
    bool quit = false;
    bool pause = false;
    int mouse_x, mouse_y = 0;
    int ext_force = 0;
    Events();
    void pool_events();
};
