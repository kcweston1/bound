#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "constants.h"
#include "sprite.h"
#include "player.h"

class SDL_Renderer;
class SDL_Window;

static const int TicksPerFrame = 1000 / Fps;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    bool init(SDL_Window* window);
    void free();
    SDL_Renderer* getSDLRenderer();
    void submit(Sprite* sprite);
    void render();
private:
    std::vector<Sprite*> renderables_;
    SDL_Renderer* renderer_;
    int cycles_;
    uint32_t ticks_;
};

#endif