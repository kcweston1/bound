#include <SDL2/SDL.h>
#include "timer.h"

Timer::Timer()
    : running_(false), ticks_(0)
{}


bool Timer::isRunning() const
{
    return running_;
}


void Timer::start()
{
    running_ = true;
    ticks_ = SDL_GetTicks();
}


void Timer::stop()
{
    running_ = false;
    ticks_ = 0;
}


uint32_t Timer::time() const
{
    return SDL_GetTicks() - ticks_;
}