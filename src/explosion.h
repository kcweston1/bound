#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL2/SDL.h>
#include <memory>
#include "sprite.h"
#include "timer.h"

static const int Frequency = 1500;
static const int ExplodeTime = 500;
static const std::size_t ExplodeSize = 74;

class Explosion
{
public:
	Explosion()
		: frequency_(Frequency), active_(false), rectIndex_(0)
	{
		timer_.start();
	}
	Explosion(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet, int frequency, uint32_t delay=0)
		: frequency_(frequency), active_(false), rectIndex_(0), sprite_(Sprite(dst, spriteSheet))
	{
		timer_.start(delay);
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
			if (timer_.time() >= Frequency)
			{
				active_ = true;
				rectIndex_ = 0;
				sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect(rectIndex_));
				timer_.start();
			}
			return;
		}

		if (timer_.time() >= ExplodeTime / ExplodeSize)
		{
			rectIndex_++;
			if (rectIndex_ >= ExplodeSize)
				active_ = false;
			else
				sprite_.setSrcRect(sprite_.getSpriteSheet()->getSrcRect(rectIndex_));
			timer_.start();
		}
	}
private:
	int rectIndex_;
	Sprite sprite_;
	uint32_t frequency_;
	bool active_;
	Timer timer_;
};

#endif