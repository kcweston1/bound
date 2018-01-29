#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player();
    Player(const SDL_Rect& dst);
    Player(const SDL_Rect& dst, const SDL_Rect& src);

    void move();
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
