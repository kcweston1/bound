#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include "entity.h"

const int W = 640;
const int H = 480;

class Game
{
public:
    Game(); //use an init funtion
    ~Game();
    bool init();
    void mainLoop();
    bool eventHandler();
    void keyboardEvent(int key, bool state, bool repeat);
    void mouseButtonEvent(int x, int y, uint8_t button, bool state);
private:
    std::vector<Entity> tiles_;
    std::vector<SDL_Rect> srcRects_;
    SDL_Window * window_;
    SDL_Renderer * renderer_;
    SDL_Texture * texture_;
};

#endif
