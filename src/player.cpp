#include "player.h"
#include "constants.h"
#include <cmath>

//TODO: make Player::init()
Player::Player()
    : sprite_(), dir_(0), runState_(STAND), x_(0), y_(0), dx_(0), dy_(0), speed_(5.0f),
      accel_(0), targetX_(0), targetY_(0), alive_(true)
{
    timer_.start();
}


Player::Player(std::shared_ptr<SpriteSheet> spriteSheet)
    : sprite_(spriteSheet), dir_(0), runState_(STAND), x_(0), y_(0), dx_(0), dy_(0), speed_(1),
      accel_(0), targetX_(0), targetY_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet)
    : sprite_(dst, spriteSheet), dir_(0), runState_(STAND), x_(dst.x), y_(dst.y), dx_(0), dy_(0),
      speed_(1), accel_(0), targetX_(0), targetY_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet)
    : sprite_(dst, src, spriteSheet), dir_(0), runState_(STAND), x_(dst.x), y_(dst.y),
      dx_(0), dy_(0), speed_(1), accel_(0), targetX_(0), targetY_(0),
      alive_(true)
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
            dir_ = WEST;
        else if (dy_ > pi7_8.second && dy_ <= pi5_8.second) //Southwest
            dir_ = SOUTHWEST;
        else if (dy_ > pi5_8.second) //South
            dir_ = SOUTH;
        else if (dy_ >= pi11_8.second && dy_ < pi9_8.second) //Northwest
            dir_ = NORTHWEST;
        else //North
            dir_ = NORTH;
    }
    else if (dx_ > 0)
    {
        if (dy_ >= pi15_8.second && dy_ <= pi_8.second) //East
            dir_ = EAST;
        else if (dy_ > pi_8.second && dy_ <= pi3_8.second) //Southeast
            dir_ = SOUTHEAST;
        else if (dy_ > pi3_8.second) //South
            dir_ = SOUTH;
        else if (dy_ >= pi13_8.second && dy_ < pi15_8.second) //Northeast
            dir_ = NORTHEAST;
        else //North
            dir_ = NORTH;
    }
    else
    {
        if (dy_ > 0) //South
            dir_ = SOUTH;
        else if (dy_ < 0) //North
            dir_ = NORTH;
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


float Player::getAccel()
{
    return accel_;
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


Sprite& Player::getSprite()
{
    return sprite_;
}


bool Player::isAlive()
{
    return alive_;
}


bool Player::setAlive(bool alive)
{
    alive_ = alive;
}



void Player::move(const Level& level)
{
    //Update Acceleration
    if (accel_ < 1)
    {
        accel_ += 0.02;
    }
    
    checkCollision(level);
    
    //Update real position
    x_ += std::abs(targetX_ - x_) < std::abs(accel_ * speed_ * dx_) ? targetX_ - x_ : accel_ * speed_ * dx_;
    y_ += std::abs(targetY_ - y_) < std::abs(accel_ * speed_ * dy_) ? targetY_ - y_ : accel_ * speed_ * dy_;

    //Update discrete position
    SDL_Rect current = sprite_.getDstRect();
    current.x = x_;
    current.y = y_;

    //Has target been met?
    if (current.x == targetX_)
    {
        dx_ = 0;
    }
    if (current.y == targetY_)
    {
        dy_ = 0;
    }

    //Store updated position
    sprite_.setDstRect(current);
    
    if (dy_ != 0 || dx_ != 0)
    {
        if (timer_.time() > 100)
        {
            ++runState_;
            if (runState_ == 8) runState_ = 0;
            timer_.start();
        }
    }
    else
    {
        accel_ = 0;
        runState_ = STAND;
    }
    
    //Update src rect to correspond to correct sprite
    sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect((dir_ * 8) + runState_));
}


void Player::updateMovement(int mouseX, int mouseY)
{
    SDL_Rect dst = sprite_.getDstRect();
    targetX_ = mouseX - dst.w / 2;
    targetY_ = mouseY - (3 * dst.h) / 4 ;

    if (targetX_ == dst.x && targetY_ == dst.y)
        return;

    dx_ = (targetX_ - dst.x) / hypot((targetX_ - dst.x), (targetY_ - dst.y));
    dy_ = (targetY_ - dst.y) / hypot((targetX_ - dst.x), (targetY_ - dst.y));

    setDirection();
}


void Player::checkCollision(const Level& level)
{
    checkTileCollision(level);
    checkScreenCollision();
    checkObjectCollision();
}


void Player::checkTileCollision(const Level& level)
{
    SDL_Rect newPosY = sprite_.getDstRect();
    SDL_Rect newPosX = sprite_.getDstRect();
    newPosX.x = x_ + (accel_ * speed_ * dx_);
    newPosY.y = y_ + (accel_ * speed_ * dy_);
    for (const SDL_Rect& rect : level.getBoundary())
    {
        if (SDL_HasIntersection(&rect, &newPosX))
            dx_ = 0;
        if (SDL_HasIntersection(&rect, &newPosY))
            dy_ = 0;
    }
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
         << " accel:" << p.getAccel()
         << " target x:" << p.getTargetX()
         << " target y:" << p.getTargetY()
         << " alive:" << p.isAlive();

    return cout;
}
