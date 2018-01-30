#include <vector>
#include "level.h"

Level::Level() {}

Level::Level(std::vector<int> data)
    : data_(data)
{}


void Level::generate(SDL_Texture* texture, 
                     const std::vector<int>& data, 
                     int clipWidth, 
                     int clipHeight, 
                     int tileWidth, 
                     int tileHeight)
{
    /*
    // Check the texture is not null.
    if (texture == nullptr)
        return;

    tiles_.clear();

    int texW, texH = 0;
    SDL_QueryTexture(texture_, nullptr, nullptr, &texW, &texH);

    SDL_Rect src = {0, 0, clipWidth, clipHeight};
    SDL_Rect dst = {0, 0, tileWidth, tileHeight};

    std::for_each(data.begin(), data.end(),
        [&, src, dst](int i) : mutable
        {
            src.x = clipWidth * i % texW;
            src.y = (clipWidth * i / texW) * clipHeight;
            dst.x = (dst.x + tileWidth) % Width;
            if (dst.x == 0)
                dst.y += tileHeight;
            tiles_.push_back(Sprite(dst, src, texture));
        }
    );
    */
}


std::vector<int> Level::getData()
{
    return data_;
}


void Level::setData(std::vector<int> data)
{
    data_ = data;
}
