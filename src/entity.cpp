#include "entity.h"

Entity::Entity()
    : Entity({0, 0, 1, 1})
{}


Entity::Entity(const SDL_Rect& dst)
    : dst_(dst)
{}


const SDL_Rect& Entity::getDstRect() const
{
    return dst_;
}


void Entity::setDstRect(const SDL_Rect& dst)
{
    dst_ = dst;
}