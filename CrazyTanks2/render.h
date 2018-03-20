#ifndef RENDER_H
#define RENDER_H
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "gameprocesspart.h"

using namespace std;

class Render : public GameProcessPart
{
public:
    Render();
    void draw();
    void process();
};

#endif // RENDER_H
