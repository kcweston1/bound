#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "spritesheet.h"

class Sprite : public Entity
{
public:
    Sprite(SpriteSheet& spriteSheet);
    Sprite(const SDL_Rect& dst, SpriteSheet& spriteSheet);
    Sprite(const SDL_Rect& dst, const SDL_Rect& src, SpriteSheet& spriteSheet);
    const SDL_Rect& getSrcRect() const;
    void setSrcRect(const SDL_Rect& src);
    SpriteSheet& getSpriteSheet();
    void setSpriteSheet(SpriteSheet& spriteSheet);
protected:
    SDL_Rect src_;
    SpriteSheet& spriteSheet_;
};

#endif