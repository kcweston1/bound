#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NDEBUG
#include <cassert>
#include <cmath>

static const int W = 1280;
static const int H = 960;
static const int PlayerWidth = 32;
static const int PlayerHeight = 32;
static const float PI = 3.14159;

//Used to calculate player direction
static const std::pair<float, float> pi_8(cos(PI/8), sin(PI/8));
static const std::pair<float, float> pi3_8(cos((3*PI)/8), sin((3*PI)/8));
static const std::pair<float, float> pi5_8(cos((5*PI)/8), sin((5*PI)/8));
static const std::pair<float, float> pi7_8(cos((7*PI)/8), sin((7*PI)/8));
static const std::pair<float, float> pi9_8(cos((9*PI)/8), sin((9*PI)/8));
static const std::pair<float, float> pi11_8(cos((11*PI)/8), sin((11*PI)/8));
static const std::pair<float, float> pi13_8(cos((13*PI)/8), sin((13*PI)/8));
static const std::pair<float, float> pi15_8(cos((15*PI)/8), sin((15*PI)/8));

//Used to help standardize player sprite sheets, corresponds to player direction
//Current sprite sheet: Player.png
static const int NORTH = 1;
static const int NORTHEAST = 2;
static const int EAST = 0;
static const int SOUTHEAST = 5;
static const int SOUTH = 4;
static const int SOUTHWEST = 6;
static const int WEST = 7;
static const int NORTHWEST = 3;

//Used to denote the column of the current sprite sheet that represents the
//player while standing still
static const int STAND = 2;

#endif
