#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Level
{
public:
    Level();
    Level(std::vector<int>);

    std::vector<int> getData();
    void setData(std::vector<int>);
private:
    std::vector<int> data_;
};

#endif
