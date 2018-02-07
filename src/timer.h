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
    void start(int delay=0);
    void stop();
    int time() const;
private:
    bool running_;
    int ticks_;
};

#endif