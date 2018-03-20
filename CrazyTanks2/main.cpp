#include <iostream>
#include <vector>
#include <conio.h>
#include "cell.h"
#include "tank.h"
#include "bullet.h"
#include "bulletaction.h"
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <future>
#include "gamemanager.h"
#include "world.h"

using namespace std;

int main()
{
    srand(time(0));

    //create and start game world
    World w;
    w.startGame();

    return 0;
}
