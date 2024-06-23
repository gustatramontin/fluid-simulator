
class Events {
    SDL_Event e;
public:
    bool quit = false;
    bool pause = false;
    Events();
    void pool_events();
};
