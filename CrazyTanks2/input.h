#ifndef INPUT_H
#define INPUT_H
#include <conio.h>
#include <thread>
#include <chrono>
#include "gameprocesspart.h"

class Input : public GameProcessPart
{
public:
    Input();
    void process();
};

#endif // INPUT_H
