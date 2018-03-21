#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include "cell.h"
#include "tank.h"

using namespace std;

class Bullet
{
public:
    Bullet(int x, int y, Type type, Direction d);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    Type getType() const;
    void setType(Type type);
    Direction getDirection() const;
    void setDirection(Direction direction);
    bool getIsShotMade() const;
    void setIsShotMade(bool isShotMade);

private:
    int x_;
    int y_;
    Type type_;
    Direction direction_;
    bool isShotMade_;
};

#endif // BULLET_H
