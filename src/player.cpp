#include "player.h"


Player::Player()
    : Sprite(), dir_(0), x_(0), y_(0), dx_(0), dy_(0), speed_(1),
      targetX_(0), targetY_(0), alive_(true) 
{}


Player::Player(std::shared_ptr<SpriteSheet> spriteSheet)
    : Sprite(spriteSheet), dir_(0), x_(0), y_(0), dx_(0), dy_(0), speed_(1),
      targetX_(0), targetY_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet)
    : Sprite(dst, spriteSheet), dir_(0), x_(dst.x), y_(dst.y), dx_(0), dy_(0),
      speed_(1), targetX_(0), targetY_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet)
    : Sprite(dst, src, spriteSheet), dir_(0), x_(dst.x), y_(dst.y),
      dx_(0), dy_(0), speed_(1), targetX_(0), targetY_(0), alive_(true)
{}


float Player::getDirection()
{
    return dir_;
}


void Player::setDirection(float dir)
{
    dir_ = dir;
}


float Player::getX()
{
    return x_;
}


void Player::setX(float x)
{
    x_ = x;
}


float Player::getY()
{
    return y_;
}


void Player::setY(float y)
{
    y_ = y;
}


float Player::getDx()
{
    return dx_;
}


void Player::setDx(float dx)
{
    dx_ = dx;
}


float Player::getDy()
{
    return dy_;
}


void Player::setDy(float dy)
{
    dy_ = dy;
}


float Player::getSpeed()
{
    return speed_;
}


void Player::setSpeed(float speed)
{
    speed_ = speed;
}


int Player::getTargetX()
{
    return targetX_;
}


void Player::setTargetX(int targetX)
{
    targetX_ = targetX;
}


int Player::getTargetY()
{
    return targetY_;
}


void Player::setTargetY(int targetY)
{
    targetY_ = targetY;
}


bool Player::isAlive()
{
    return alive_;
}


bool Player::setAlive(bool alive)
{
    alive_ = alive;
}



void Player::move()
{
    checkCollision();

    //Update real position
    x_ += speed_ * dx_;
    y_ += speed_ * dy_;

    //Update discrete position
    dst_.x = x_;
    dst_.y = y_;
}

void Player::checkCollision()
{
    checkTileCollision();
    checkScreenCollision();
    checkObjectCollision();
}


void Player::checkTileCollision()
{
/*    
     checkTileCollision should check against the preset collision rects
     to determine whether a move should be made.
*/
}


void Player::checkScreenCollision()
{
    
/*
      checkScreenCollision should check whether the player will be out of bounds
      after moving. If yes, prevent movement.
*/
}


void Player::checkObjectCollision()
{
/*
      checkObjectCollision should check whether the player is currently colliding
      with an object that affects the player (e.g. causes death)
*/

}
