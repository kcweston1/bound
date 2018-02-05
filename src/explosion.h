#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL2/SDL.h>
#include "sprite.h"

static const uint32_t Frequency = 2000;
static const uint32_t ExplodeTime = 1000;
static const std::size_t ExplodeSize = 74;

class Explosion
{
public:
	Explosion()
		: frequency_(Frequency), active_(false), rectIndex_(0)
	{
		ticks_ = SDL_GetTicks();
	}
	Sprite& getSprite()
	{
		return sprite_;
	}
	bool getActive() const
	{
		return active_;
	}
	void update()
	{
		if (!active_)
		{	
			if (SDL_GetTicks() - ticks_ >= Frequency)
			{
				active_ = true;
				rectIndex_ = 0;
				sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect(rectIndex_));
				ticks_ = SDL_GetTicks();
			}
			return;
		}

		if (SDL_GetTicks() - ticks_ >= ExplodeTime / ExplodeSize)
		{
			rectIndex_++;
			if (rectIndex_ >= ExplodeSize)
				active_ = false;
			else
				sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect(rectIndex_));
			ticks_ = SDL_GetTicks();
		}
	}
private:
	int rectIndex_;
	Sprite sprite_;
	uint32_t frequency_;
	uint32_t ticks_;
	bool active_;
};

#endif