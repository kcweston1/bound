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
	start_ = std::chrono::high_resolution_clock::now();
    running_ = true;
    ticks_ = SDL_GetTicks() + delay;
}


void Timer::stop()
{
    running_ = false;
    ticks_ = 0;
}


float Timer::time() const
{
	std::chrono::duration<float, std::milli> dur = std::chrono::high_resolution_clock::now() - start_;
	return dur.count();
    //return static_cast<int>(SDL_GetTicks()) - ticks_;
}