#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include "entity.h"
#include "spritesheet.h"

class Sprite : public Entity
{
public:
    Sprite();
    Sprite(std::shared_ptr<SpriteSheet> spriteSheet);
    Sprite(const SDL_Rect& dst, std::shared_ptr<SpriteSheet> spriteSheet);
    Sprite(const SDL_Rect& dst, const SDL_Rect& src, std::shared_ptr<SpriteSheet> spriteSheet);
    void operator=(const Sprite& sprite);
    const SDL_Rect& getSrcRect() const;
    void setSrcRect(const SDL_Rect& src);
    std::shared_ptr<SpriteSheet> getSpriteSheet();
    void setSpriteSheet(std::shared_ptr<SpriteSheet> spriteSheet);
protected:
    SDL_Rect src_;
    std::shared_ptr<SpriteSheet> spriteSheet_;
};

#endif