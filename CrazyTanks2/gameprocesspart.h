#ifndef GAMEPROCESSPART_H
#define GAMEPROCESSPART_H
#include "gamemanager.h"

class GameProcessPart
{
protected:
    GameManager *m;

public:
    GameProcessPart();
    virtual void process() = 0;
};

#endif // GAMEPROCESSPART_H
