#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>
#include "sprite.h"
#include "spritesheet.h"
#include "level.h"
#include "timer.h"
#include "vec2.h"

class Player
{
public:
    Player();

    void init(const Vec2& position);
    int getDirection() const;
    void setDirection();
    float getSpeed();
    void setSpeed(float speed);
    float getAccel();
    Sprite& getSprite();
    void setSprite(const Sprite& sprite);
    bool isAlive();
    bool setAlive(bool alive);
    Vec2 getPosition() const;
    void setPosition(const Vec2& position);
    void setTarget(int x, int y);
    
    void update();
    //void checkCollision(const Level& level);
    //void checkTileCollision(const Level& level);
    //void checkScreenCollision();
    //void checkObjectCollision();

    
    
    
private:
    Sprite sprite_;
    Timer timer_;
    Timer moveTimer_;
    int dir_; //Dictates which direction the player sprite is facing, 0-7
    int runState_;
    Vec2 position_;
    Vec2 target_;
    Vec2 normal_;
    Vec2 velocity_;
    float speed_;
    float accel_; //0.0-1.0
    bool alive_;
};

std::ostream & operator<<(std::ostream & cout, Player & p);

#endif
