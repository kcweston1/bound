#include "sprite.h"

Sprite::Sprite()
	: Sprite({0, 0, 1, 1}, nullptr)
{}

Sprite::Sprite(std::shared_ptr<SpriteSheet> spriteSheet)
    : Sprite({0, 0, 1, 1}, spriteSheet)
{}

Sprite::Sprite(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet)
    : Entity(dst), src_({0, 0, 1, 1}), spriteSheet_(spriteSheet)
{
	if (spriteSheet_ != nullptr)
	    src_ = {0, 0, spriteSheet_->getWidth(), spriteSheet_->getHeight()};
}


void Sprite::operator=(const Sprite& sprite)
{
    src_ = sprite.src_;
    dst_ = sprite.dst_;
    spriteSheet_ = sprite.spriteSheet_;
}


Sprite::Sprite(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet)
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


std::shared_ptr<SpriteSheet> Sprite::getSpriteSheet()
{
    return spriteSheet_;
}


void Sprite::setSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet)
{
    spriteSheet_ = spriteSheet;
}