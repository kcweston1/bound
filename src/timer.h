#ifndef TIMER_H
#define TIMER_H

/*
    Simple class to model a timer with basic timing functionality.
*/

#include <chrono>

class Timer
{
public:
    Timer();
    bool isRunning() const;
    void start(int delay=0);
    void stop();
    float time() const;
private:
    bool running_;
    int ticks_;
    std::chrono::high_resolution_clock::time_point start_;
};

#endif