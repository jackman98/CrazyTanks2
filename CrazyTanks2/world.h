#ifndef WORLD_H
#define WORLD_H
#include <thread>
#include "render.h"
#include "input.h"
#include "logic.h"
#include "ai.h"
#include "timer.h"
#include "gamemanager.h"

using namespace std;

class World
{
public:
    World();
    void startGame();

private:
    Render render;
    Input input;
    Logic logic;
    Timer timer;
    EnemyTankAI ai;

    GameManager *m;

    void buildField();
    void generateFortress(int x, int y);
    void generateEnemyTanks(int countOfTanks);
    bool checkNeighboringCells(int x, int y, TypeCell t, int radius = 2);
};

#endif // WORLD_H
