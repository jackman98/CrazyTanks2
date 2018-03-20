#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <iostream>
#include "bullet.h"
#include "constants.h"

using namespace std;

class GameManager
{
public:
  static GameManager& instance()
  {
    static GameManager singleton;
    return singleton;
  }

  int score;
  int timeInGame;
  bool loss;
  bool victory;
  bool stopGame;
  vector<Bullet *> myBullets;
  vector<Bullet *> enemyBullets;
  vector<Tank *> enemyTanks;
  vector<vector<Cell>> field;

  Tank *tank;
private:
  GameManager() : score(0), timeInGame(0), loss(false), victory(false), stopGame(false) {}
  ~GameManager() {}
  GameManager(const GameManager&);
  GameManager& operator=(const GameManager&);
};

#endif // GAMEMANAGER_H
