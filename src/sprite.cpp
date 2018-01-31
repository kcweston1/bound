#include "sprite.h"

Sprite::Sprite(SpriteSheet& spriteSheet)
    : Sprite({0, 0, 1, 1}, spriteSheet)
{}

Sprite::Sprite(const SDL_Rect& dst, SpriteSheet& spriteSheet)
    : Entity(dst), src_({0, 0, 1, 1}), spriteSheet_(spriteSheet)
{
    src_ = {0, 0, spriteSheet_.getWidth(), spriteSheet_.getHeight()};
}


Sprite::Sprite(const SDL_Rect& dst, const SDL_Rect& src, SpriteSheet& spriteSheet)
    : Entity(dst), src_(src), spriteSheet_(spriteSheet)
{}


const SDL_Rect& Sprite::getSrcRect() const
{
    return src_;
}


void Sprite::setSrcRect(const SDL_Rect& src)
{
    src_ = src;
}


SpriteSheet& Sprite::getSpriteSheet()
{
    return spriteSheet_;
}


void Sprite::setSpriteSheet(SpriteSheet& spriteSheet)
{
    spriteSheet_ = spriteSheet;
}