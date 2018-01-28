#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>

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
    SDL_Window * window_;
    SDL_Renderer * renderer_;
};

#endif
