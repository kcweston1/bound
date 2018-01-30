#include "player.h"

Player::Player(SDL_Texture* texture)
    : Sprite(texture), dir_(0), dx_(0), dy_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, SDL_Texture* texture)
    : Sprite(dst, texture), dir_(0), dx_(0), dy_(0), alive_(true)
{}


Player::Player(const SDL_Rect& dst, const SDL_Rect& src, SDL_Texture* texture)
    : Sprite(dst, src, texture), dir_(0), dx_(0), dy_(0), alive_(true)
{}


void Player::move()
{
    checkCollision();
    
    dst_.x += dx_;
    dst_.y += dy_;
}


float Player::getDirection()
{
    return dir_;
}


void Player::setDirection(float dir)
{
    dir_ = dir;
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
      checkTileCollision should check the status of the tile the player will be on
      AFTER moving. If the next tile is not a type which the player can stand on,
      prevent movement.
      Ideally there will be a tile class which will contain a member that
      tells whether the player can stand on it;
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
