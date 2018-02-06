#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>
#include "sprite.h"
#include "spritesheet.h"
#include "level.h"
#include "timer.h"

class Player
{
public:
    Player();
    Player(std::shared_ptr<SpriteSheet> spriteSheet);
    Player(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet);
    Player(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet);

    
    float getDirection();
    void setDirection();
    float getX();
    void setX(float x);
    float getY();
    void setY(float y);
    float getDx();
    void setDx(float dx);
    float getDy();
    void setDy(float dy);
    float getSpeed();
    void setSpeed(float speed);
    float getAccel();
    int getTargetX();
    void setTargetX(int targetX);
    int getTargetY();
    void setTargetY(int targetY);
    Sprite& getSprite();
    bool isAlive();
    bool setAlive(bool alive);
    
    void move(const Level& level);
    void updateMovement(int mouseX, int mouseY);
    void checkCollision(const Level& level);
    void checkTileCollision(const Level& level);
    void checkScreenCollision();
    void checkObjectCollision();

    
    
    
private:
    Sprite sprite_;
    Timer timer_;
    int dir_; //Dictates which direction the player sprite is facing, 0-7
    int runState_;
    float x_;
    float y_;
    float dx_;
    float dy_;
    float speed_;
    float accel_; //0.0-1.0
    int targetX_;
    int targetY_;
    bool alive_;
};

std::ostream & operator<<(std::ostream & cout, Player & p);

#endif
