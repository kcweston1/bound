#include <SDL2/SDL.h>
#include "entity.h"

Entity::Entity()
    : Entity({0, 0, 1, 1}, {0, 0, 1, 1})
{}


Entity::Entity(const SDL_Rect& dst)
    : Entity(dst, {0, 0, 1, 1})
{}


Entity::Entity(const SDL_Rect& dst, const SDL_Rect& src)
    : dst_(dst), src_(src)
{}


const SDL_Rect& Entity::getSrcRect() const
{
    return src_;
}


const SDL_Rect& Entity::getDstRect() const
{
    return dst_;
}


void Entity::setSrcRect(const SDL_Rect& src)
{
    src_ = src;
}


void Entity::setDstRect(const SDL_Rect& dst)
{
    dst_ = dst;
}