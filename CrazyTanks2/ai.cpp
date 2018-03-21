#include "ai.h"

EnemyTankAI::EnemyTankAI()
{
}

void EnemyTankAI::process()
{
    int delay = 300;
    int offsetDelay = 200;

    while (!m->stopGame){
        shoting();
        this_thread::sleep_for(chrono::milliseconds(rand() % delay + offsetDelay));
        moving();
    }
}

Direction EnemyTankAI::getRandomDirection()
{
    switch (rand() % 4) {
    case 0:
        return Direction::UP;
    case 1:
        return Direction::DOWN;
    case 2:
        return Direction::RIGHT;
    case 3:
        return Direction::LEFT;
    }
    return Direction::NONE;
}

void EnemyTankAI::moving()
{
    for(size_t i = 0; i < m->enemyTanks.size(); ++i) {
        m->enemyTanks[i]->move(m->field, getRandomDirection());
    }
}

void EnemyTankAI::shoting()
{
    for(size_t i = 0; i < m->enemyTanks.size(); ++i) {
        auto enemyTank = m->enemyTanks[i];
        bool isNeedShot = static_cast<bool>(rand() % 3);
        if (isNeedShot) {
            //create new bullet and add in enemyBullets pull
            Bullet *b = new Bullet(enemyTank->getX(), enemyTank->getY(),
                                   enemyTank->getType(), enemyTank->getDirection());
            m->enemyBullets.push_back(b);
        }
    }
}
