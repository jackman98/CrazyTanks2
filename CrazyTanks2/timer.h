#ifndef TIMER_H
#define TIMER_H
#include "gameprocesspart.h"
#include <thread>
#include <chrono>

class Timer : public GameProcessPart
{
public:
    Timer();

    void process();
};

#endif // TIMER_H
