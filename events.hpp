
class Events {
    SDL_Event e;
public:
    bool quit = false;
    bool pause = false;
    int mouse_x, mouse_y = 0;
    bool ext_force = false;
    int ext_force_dir = 1;
    Events();
    void pool_events();
};
