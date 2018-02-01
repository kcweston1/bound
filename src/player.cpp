#include "player.h"
#include "constants.h"
#include <cmath>

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


void Player::setDirection()
{
    if (dx_ < 0)
    {
        if (dy_ >= pi9_8.second && dy_ <= pi7_8.second) //West
            dir_ = 6;
        else if (dy_ > pi7_8.second && dy_ <= pi5_8.second) //Southwest
            dir_ = 5;
        else if (dy_ > pi5_8.second) //South
            dir_ = 4;
        else if (dy_ >= pi11_8.second && dy_ < pi9_8.second) //Northeast
            dir_ = 7;
        else //North
            dir_ = 0;
    }
    else if (dx_ > 0)
    {
        if (dy_ >= pi15_8.second && dy_ <= pi_8.second) //East
            dir_ = 2;
        else if (dy_ > pi_8.second && dy_ <= pi3_8.second) //Southeast
            dir_ = 3;
        else if (dy_ > pi3_8.second) //South
            dir_ = 4;
        else if (dy_ >= pi13_8.second && dy_ < pi15_8.second) //Northeast
            dir_ = 1;
        else //North
            dir_ = 0;
    }
    else
    {
        if (dy_ > 0) //South
            dir_ = 4;
        else if (dy_ < 0) //North
            dir_ = 0;
        //else do nothing, as dy_ and dx_ are both 0;
    }
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

    //Has target been met?
    if (dst_.x == targetX_)
    {
        dx_ = 0;
    }
    if (dst_.y == targetY_)
    {
        dy_ = 0;
    }
}


void Player::updateMovement(int mouseX, int mouseY)
{
    targetX_ = mouseX;
    targetY_ = mouseY;

    dx_ = (mouseX - dst_.x) / hypot((mouseX - dst_.x), (mouseY - dst_.y));
    dy_ = (mouseY - dst_.y) / hypot((mouseX - dst_.x), (mouseY - dst_.y));

    setDirection();
    
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


std::ostream & operator<<(std::ostream & cout, Player & p)
{
    cout << "dir:" << p.getDirection()
         << " x:" << p.getX()
         << " y:" << p.getY()
         << " dx:" << p.getDx()
         << " dy:" << p.getDy()
         << " speed:" << p.getSpeed()
         << " target x:" << p.getTargetX()
         << " target y:" << p.getTargetY()
         << " alive:" << p.isAlive();

    return cout;
}
