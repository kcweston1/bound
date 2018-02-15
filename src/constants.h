#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NDEBUG
#include <cassert>
#define _USE_MATH_CONSTANTS
#include <cmath>

static const int W = 1280;
static const int H = 960;
static const int PLAYER_WIDTH = 32;
static const int PLAYER_HEIGHT = 32;
static const int FPS = 60;
static const float RENDER_INTERVAL = 1000.0f/FPS;

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
