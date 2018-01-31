#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include "sprite.h"
#include "level.h"
#include "player.h"
#include "spritesheet.h"
#include "constants.h"

class Game
{
public:
    Game(); //use an init funtion
    ~Game();
    bool init();
    void initLevels();
    void mainLoop();
    bool eventHandler();
    void keyboardEvent(int key, bool state, bool repeat);
    void mouseButtonEvent(int x, int y, uint8_t button, bool state);
private:
    //std::unique_ptr<Sprite> player_;
    //Player player_;
    std::vector<Sprite> tiles_;
    std::vector<SDL_Rect> srcRects_;
    std::vector<Level> levels_;
    SDL_Window * window_;
    SDL_Renderer * renderer_;
    SpriteSheet tileSheet_;
};

#endif
