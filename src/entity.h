#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

/*
    Class to model a game entity. This keeps track of
    the source rect(the object's location on the texture),
    and the destination rect (the object's location on the
    screen).
*/

class Entity
{
public:
    Entity();
    Entity(const SDL_Rect& dst);
    const SDL_Rect& getDstRect() const;
    void setDstRect(const SDL_Rect& dst);
protected:
    SDL_Rect dst_;
};

#endif