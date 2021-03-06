#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include <memory>
#include "sprite.h"
#include "level.h"
#include "player.h"
#include "spritesheet.h"
#include "constants.h"
#include "config.h"
#include "renderer.h"
#include "explosion.h"

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
    void issueMoveCommand(int mouseX, int mouseY);
    
private:
    int levelNumber_;
    Player player_;
    Level level_;
    SDL_Window * window_;
    Renderer renderer_;
    std::shared_ptr<SpriteSheet> tileSheet_;
    std::shared_ptr<SpriteSheet> playerSheet_;
    std::shared_ptr<SpriteSheet> explosionSheet_;
    std::vector<Explosion> explosions_;
};

#endif
