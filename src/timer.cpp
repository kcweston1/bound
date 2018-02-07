#include <SDL2/SDL.h>
#include "timer.h"

Timer::Timer()
    : running_(false), ticks_(0)
{}


bool Timer::isRunning() const
{
    return running_;
}


void Timer::start(int delay)
{
    running_ = true;
    ticks_ = SDL_GetTicks() + delay;
}


void Timer::stop()
{
    running_ = false;
    ticks_ = 0;
}


int Timer::time() const
{
    return static_cast<int>(SDL_GetTicks()) - ticks_;
}