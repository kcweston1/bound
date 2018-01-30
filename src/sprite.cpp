#include "sprite.h"

Sprite::Sprite(SDL_Texture* texture)
{

}


Sprite::Sprite(const SDL_Rect& dst, SDL_Texture* texture)
	: Entity(dst), src_({0, 0, 1, 1}), texture_(texture)
{
	if (texture_ != nullptr)
	{
		int w, h = 0;
		SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h);
		src_ = {0, 0, w, h};
	}
}


Sprite::Sprite(const SDL_Rect& dst, const SDL_Rect& src, SDL_Texture* texture)
	: Entity(dst), src_(src), texture_(texture)
{}


const SDL_Rect& Sprite::getSrcRect() const
{
	return src_;
}


void Sprite::setSrcRect(const SDL_Rect& src)
{
	src_ = src;
}


SDL_Texture* Sprite::getTexture()
{
	return texture_;
}


void Sprite::setTexture(SDL_Texture* texture)
{
	texture_ = texture;
}