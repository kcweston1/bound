#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"

class Sprite : public Entity
{
public:
	Sprite(SDL_Texture* texture);
	Sprite(const SDL_Rect& dst, SDL_Texture* texture);
	Sprite(const SDL_Rect& dst, const SDL_Rect& src, SDL_Texture* texture);
	const SDL_Rect& getSrcRect() const;
	void setSrcRect(const SDL_Rect& src);
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* texture);
protected:
	SDL_Rect src_;
	SDL_Texture* texture_;
};

#endif