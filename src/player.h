#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

class Player : public Sprite
{
public:
    Player(SDL_Texture* texture);
    Player(const SDL_Rect& dst, SDL_Texture* texture);
    Player(const SDL_Rect& dst, const SDL_Rect& src, SDL_Texture* texture);

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
