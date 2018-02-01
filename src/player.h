#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "sprite.h"
#include "spritesheet.h"

class Player : public Sprite
{
public:
    Player();
    Player(std::shared_ptr<SpriteSheet> spriteSheet);
    Player(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet);
    Player(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet);

    float getDirection();
    void setDirection(float dir);
    void move();
    void checkCollision();
    void checkTileCollision();
    void checkScreenCollision();
    void checkObjectCollision();
    
    
private:
    float dir_; //direction the player sprite is "facing", between 0 and 360
    float dx_;
    float dy_;
    bool alive_;
};

#endif
