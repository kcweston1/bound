#include <vector>
#include "level.h"

Level::Level() {}

Level::Level(std::vector<int> data)
    : data_(data)
{}


void Level::generate(std::shared_ptr<SpriteSheet> spriteSheet,
        const std::vector<int>& indicies, int tileW, int tileH)
{
    int x = 0;
    int y = 0;
    for (int i : indicies)
    {
        tiles_.push_back(Sprite({x, y, tileW, tileH}, spriteSheet->getSrcRect(i), spriteSheet));
        x = std::min(x + tileW, W) % W;
        if (x == 0)
            y += tileH;
    }
}


std::vector<int> Level::getData()
{
    return data_;
}


void Level::setData(std::vector<int> data)
{
    data_ = data;
}


std::vector<Sprite>& Level::getTiles()
{
    return tiles_;
}