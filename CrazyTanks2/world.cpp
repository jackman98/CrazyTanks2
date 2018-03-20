#include "world.h"

void World:: buildField()
{
    //generation new field
    m->field.clear();
    for (int i = 0; i < HEIGHT; i++) {
        vector<Cell> row;
        for (int j = 0; j < WIDTH; j++) {
            Cell block(TypeCell::NONE);
            row.push_back(block);
        }
        m->field.push_back(row);
    }
    //generation field boundaries
    for (int i = 0; i < HEIGHT; i++) {
        m->field.at(i).at(0).setTypeCell(TypeCell::BOUNDARY);
        m->field.at(i).at(WIDTH - 1).setTypeCell(TypeCell::BOUNDARY);
    }
    for (int i = 0; i < WIDTH; i++) {
        m->field.at(0).at(i).setTypeCell(TypeCell::BOUNDARY);
        m->field.at(HEIGHT - 1).at(i).setTypeCell(TypeCell::BOUNDARY);
    }

    //generation walls
    for (int i = 0;  i < 20; ++i) {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        int widthBlock = rand() % 3 + 1;
        int heightBlock = rand() % 3 + 1;
        m->field.at(y).at(x).setTypeCell(TypeCell::WALL);

        for (int j = 1; j <= widthBlock; ++j)
            if (x + j < WIDTH - 1)
                m->field.at(y).at(x + j).setTypeCell(TypeCell::WALL);
        for (int j = 1; j <= heightBlock; ++j)
            if (y + j < HEIGHT - 1)
                m->field.at(y + j).at(x).setTypeCell(TypeCell::WALL);
    }

    generateFortress(WIDTH / 2, HEIGHT - 3);


    //generation and addition of the main tank to the field
    m->tank = new Tank(m->field, WIDTH / 2 + 4 , HEIGHT - 3, 0, TypeTank::MAIN);
    m->tank->health = MY_HEALTH;

    //generation and addition of the enemy tans to the field
    generateEnemyTanks(COUNT_OF_ENEMY_TANKS);
}

void World::generateFortress(int x, int y)
{
    m->field.at(y).at(x).setTypeCell(TypeCell::GOLD);

    for (int offsetY = -1; offsetY <= 1; ++offsetY) {
        for (int offsetX = -1; offsetX <= 1; ++offsetX) {
            if ((offsetY == 0 && offsetX == 0) || (y + offsetY >= static_cast<int>(m->field.size())) ||
                    (y + offsetY < 0) || (x + offsetX >= static_cast<int>(m->field.at(0).size())) || (x + offsetX < 0)) {
                continue;
            }
            m->field.at(y + offsetY).at(x + offsetX).setTypeCell(TypeCell::WALL);

        }
    }
}

void World::generateEnemyTanks(int countOfTanks)
{
    int i = 0;
    Tank *enemyTank;
    while (i != countOfTanks) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        //        check the place for a new tank
        if (checkNeighboringCells(x, y, TypeCell::WALL, 1) ||
                checkNeighboringCells(x, y, TypeCell::BOUNDARY, 1) ||
                checkNeighboringCells(x, y, TypeCell::ENEMY_TANK, 3) ||
                checkNeighboringCells(x, y, TypeCell::MAIN_TANK, 3)) {
            //            if the place is occupied by a wall or near a tank, we continue and generate new coordinates
            continue;
        }
        enemyTank = new Tank(m->field, x, y, i + 1, TypeTank::ENEMY);
        m->enemyTanks.push_back(enemyTank);
        ++i;
    }
}

//check the neighboring cells around the (x,y) in the presence of a symbol with a radius,
//if such a character was found returns true
bool World::checkNeighboringCells(int x, int y, TypeCell t, int radius)
{
    for (int offsetY = -1 * radius; offsetY <= 1 * radius; ++offsetY) {
        for (int offsetX = -1 * radius; offsetX <= 1 * radius; ++offsetX) {
            if ((offsetY == 0 && offsetX == 0) || (y + offsetY >= static_cast<int>(m->field.size())) ||
                    (y + offsetY < 0) || (x + offsetX >= static_cast<int>(m->field.at(0).size())) || (x + offsetX < 0)) {
                //                if we go beyond the boundaries of the field, we continue
                continue;
            }
            if (m->field.at(y + offsetY).at(x + offsetX).getTypeCell() == t)
                return true;
        }
    }
    return false;
}

World::World()
{
    m = &GameManager::instance();
}

void World::startGame()
{
    buildField();

    //create threads
    thread renderThread(&Render::process, ref(render));
    renderThread.detach();

    thread logicThread(&Logic::process, ref(logic));
    logicThread.detach();

    thread aiThread(&EnemyTankAI::process, ref(ai));
    aiThread.detach();

    thread timeThread(&Timer::process, ref(timer));
    timeThread.detach();

    input.process();

    render.draw();
}


