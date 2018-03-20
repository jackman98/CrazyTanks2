#include "timer.h"

Timer::Timer()
{
}

void Timer::process()
{
    while (!m->stopGame) {
        this_thread::sleep_for(chrono::seconds(1));
        m->timeInGame++;
    }
}
