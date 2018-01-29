#ifndef ENTITY_H
#define ENTITY_H

/*
    Class to model a game entity. This keeps track of
    the source rect(the object's location on the texture),
    and the destination rect (the object's location on the
    screen).
*/

class SDL_Rect;

class Entity
{
public:
    Entity();
    Entity(const SDL_Rect& dst);
    Entity(const SDL_Rect& dst, const SDL_Rect& src);
    const SDL_Rect& getSrcRect() const;
    const SDL_Rect& getDstRect() const;
    void setSrcRect(const SDL_Rect& src);
    void setDstRect(const SDL_Rect& dst);
private:
    SDL_Rect src_;
    SDL_Rect dst_;
};

#endif