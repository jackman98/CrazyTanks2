#ifndef AI_H
#define AI_H
#include "tank.h"
#include "gameprocesspart.h"
#include <thread>

class EnemyTankAI : public GameProcessPart
{
public:
    EnemyTankAI();
    void process();
private:
    Direction getRandomDirection();
    void moving();
    void shoting();
};

#endif // AI_H
