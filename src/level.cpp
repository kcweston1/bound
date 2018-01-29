#include <vector>
#include "level.h"

Level::Level() {}

Level::Level(std::vector<int> data)
    : data_(data)
{}


std::vector<int> Level::getData()
{
    return data_;
}


void Level::setData(std::vector<int> data)
{
    data_ = data;
}
