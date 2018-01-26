#ifndef GAME_H
#define GAME_H
#include "SDL2/SDL.h"
#include <iostream>

const int W = 640;
const int H = 480;

class Game
{
public:
    Game(); //use an init funtion
    ~Game();
    bool init();
    
private:
    SDL_Window * window_;
    SDL_Renderer * renderer_;
};

#endif
