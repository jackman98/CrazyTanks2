#ifndef BULLETACTION_H
#define BULLETACTION_H
#include <vector>
#include "tank.h"
#include "gamemanager.h"
#include "bullet.h"

using namespace std;

class BulletAction
{
    GameManager *m;
    bool checkIntersection(Bullet &b, int x, int y);
    bool checkTank(Bullet &b, Tank *t, int x, int y);
public:
    BulletAction();
    void shot(Bullet &b);
};

#endif // BULLETACTION_H
