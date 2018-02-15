#include "player.h"
#include "constants.h"
#define _USE_MATH_DEFINES
#include <cmath>

Player::Player()
{
    init(Vec2(1.0, 1.0));
}


void Player::init(const Vec2& position)
{
    speed_ = 3.0f;
    accel_ = 0.0f;
    alive_ = true;
    runState_ = STAND;
    position_ = position;
    target_ = position;
    normal_ = Vec2(0, -1);
    dir_ = Vec2::toCardinalDirection8(normal_);
    runState_ = STAND;
    sprite_.setDstRect({static_cast<int>(std::round(position.x)), 
                        static_cast<int>(std::round(position.y)), 
                        PLAYER_WIDTH,
                        PLAYER_HEIGHT});
    if (sprite_.getSpriteSheet() != nullptr)
        sprite_.setSrcRect(
            sprite_.getSpriteSheet()->getSrcRect((dir_ * 8) + runState_));
    timer_.start();
    moveTimer_.start();
}


int Player::getDirection() const
{
    return dir_;
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


Sprite& Player::getSprite()
{
    return sprite_;
}


void Player::setSprite(const Sprite& sprite)
{
    sprite_ = sprite;
}


bool Player::isAlive()
{
    return alive_;
}


bool Player::setAlive(bool alive)
{
    alive_ = alive;
}


Vec2 Player::getPosition() const
{
    return position_;
}


void Player::setPosition(const Vec2& position)
{
    position_ = position;
}


void Player::setTarget(int x, int y)
{
    target_.x = static_cast<float>(x) - 
                static_cast<float>(PLAYER_WIDTH) / 2.0f;
    target_.y = static_cast<float>(y) - 
                (3.0f * static_cast<float>(PLAYER_HEIGHT) / 4.0f);
}


void Player::update()
{
    // Update movement only if enough time has passed.
    if (moveTimer_.time() < 20)
        return;

    // Confirm we have not already at the target.
    if (position_ == target_)
        return;

    // Update Acceleration
    if (accel_ < 1)
        accel_ += 0.02;

    // Calculate tne normal vector.
    normal_ = Vec2::normalize(target_ - position_);

    // Update the cardinal direction.
    dir_ = Vec2::toCardinalDirection8(normal_);

    // Calculate the velocity.
    velocity_ = Vec2::clamp(normal_ * (speed_ * accel_), Vec2::length(target_ - position_));

    // Update the run state based on the timer.
    if (timer_.time() > 100)
    {
        ++runState_;
        if (runState_ == 8) runState_ = 0;
        timer_.start();
    }

    // Update the position.
    position_ += velocity_;

    // Set the run state if we reach the target.
    if (position_ == target_)
    {
        runState_ = STAND;
        accel_ = 0;
    }

    // Update the destination rect.
    SDL_Rect current = sprite_.getDstRect();
    current.x = static_cast<int>(std::round(position_.x));
    current.y = static_cast<int>(std::round(position_.y));
    sprite_.setDstRect(current);

    // Update the source rect.
    sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect((dir_ * 8) + runState_));

    // Restart the timer.
    moveTimer_.start();
}


/*
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
    newPosX.x = position_.x + (accel_ * speed_ * dx_);
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
      checkScreenCollision should check whether the player will be out of bounds
      after moving. If yes, prevent movement.
}


void Player::checkObjectCollision()
{
      checkObjectCollision should check whether the player is currently colliding
      with an object that affects the player (e.g. causes death)
}
*/


std::ostream & operator<<(std::ostream & cout, Player & p)
{
    cout << "dir:" << p.getDirection()
         << " speed:" << p.getSpeed()
         << " accel:" << p.getAccel()
         << " alive:" << p.isAlive();

    return cout;
}
