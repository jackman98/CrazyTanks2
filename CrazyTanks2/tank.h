#ifndef TANK_H
#define TANK_H
#include <vector>
#include <set>
#include <algorithm>
#include <cell.h>
#include "constants.h"

using namespace std;

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum class Type {
    MAIN,
    ENEMY
};

class Tank
{
public:
    Tank(vector<vector<Cell> > &field, int x, int y, int id, Type typeTank);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    int getHealth() const;
    void setHealth(int health);
    int getId() const;
    void setId(int id);
    Type getType() const;
    void setType(Type type);
    Direction getDirection() const;
    void setDirection(Direction direction);
    void move(vector<vector<Cell> > &field, Direction direction);
    void shot();
private:
    bool checkingFreePlaceBeforeTank(vector<vector<Cell> > &field, Direction direction);
    void paintTank(vector<vector<Cell> > &field, Direction direction);
    int x_;
    int y_;
    int health_;
    int id_;
    Direction direction_;
    Type type_;
};

#endif // TANK_H
