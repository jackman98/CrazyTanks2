#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include "cell.h"
#include "tank.h"

using namespace std;

class Bullet
{
public:
    Bullet(int x, int y, TypeTank type, Direction d);
    int x;
    int y;
    TypeTank type;
    Direction direction;
    bool isShotMade;
};

#endif // BULLET_H
