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

enum class TypeTank {
    MAIN,
    ENEMY
};

class Tank
{
    bool checkingFreePlaceBeforeTank(vector<vector<Cell> > &field, Direction direction);
    void paintTank(vector<vector<Cell> > &field, Direction d);

public:
    int x;
    int y;
    int health;
    int id;
    Direction direction;
    TypeTank type;

    Tank(vector<vector<Cell> > &field, int x, int y, int id, TypeTank type);
    void move(vector<vector<Cell> > &field, Direction direction);
    void shot();
};

#endif // TANK_H
