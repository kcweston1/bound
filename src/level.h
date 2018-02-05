#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "constants.h"
#include "spritesheet.h"
#include "sprite.h"

class Level
{
public:
    Level();
    Level(std::vector<int>);
    void generate(std::shared_ptr<SpriteSheet> spriteSheet,
    	const std::vector<int>& indicies, const std::vector<SDL_Rect>& boundary,
    	int tileWidth, int tileHeight);
    std::vector<int> getData();
    void setData(std::vector<int>);
    std::vector<Sprite>& getTiles();
    const std::vector<SDL_Rect>& getBoundary() const;
private:
    std::vector<Sprite> tiles_;
    std::vector<SDL_Rect> boundary_;
    std::vector<int> data_;
};

#endif
