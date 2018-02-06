#ifndef TIMER_H
#define TIMER_H

/*
    Simple class to model a timer with basic timing functionality.
*/

class Timer
{
public:
    Timer();
    bool isRunning() const;
    void start();
    void stop();
    uint32_t time() const;
private:
    bool running_;
    uint32_t ticks_;
};

#endif