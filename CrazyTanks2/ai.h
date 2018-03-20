#ifndef AI_H
#define AI_H
#include "tank.h"
#include "gameprocesspart.h"
#include <thread>

class EnemyTankAI : public GameProcessPart
{
    Direction getRandomDirection();
    void moving();
    void shoting();

public:
    EnemyTankAI();
    void process();
};

#endif // AI_H
