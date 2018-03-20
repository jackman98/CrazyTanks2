#ifndef LOGIC_H
#define LOGIC_H
#include "gameprocesspart.h"
#include "bulletaction.h"
#include <thread>
#include <chrono>

class Logic : public GameProcessPart
{
public:
    Logic();
    void process();
};

#endif // LOGIC_H
