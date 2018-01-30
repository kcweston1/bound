#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "sprite.h"

class Level
{
public:
    Level();
    Level(std::vector<int>);
    void generate(SDL_Texture* texture, const std::vector<int>& data, 
        int clipWidth, int clipHeight, int tileWidth, int tileHeight);
    std::vector<int> getData();
    void setData(std::vector<int>);
private:
    std::vector<Sprite> tiles_;
    std::vector<int> data_;
};

#endif
