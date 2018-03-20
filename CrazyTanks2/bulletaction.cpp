#include "bulletaction.h"

BulletAction::BulletAction()
{
    m = &GameManager::instance();
}

//processing the intersection with tanks and walls
bool BulletAction::checkIntersection(Bullet &b, int x, int y) {
    Cell *cell = &(m->field[y][x]);
    if (cell->getTypeCell() == TypeCell::BOUNDARY) {
        b.isShotMade = false;
        return true;
    }

    if (cell->getTypeCell() == TypeCell::WALL) {
        if (--cell->strength == 0) {
            cell->setTypeCell(TypeCell::NONE);
        }
        b.isShotMade = false;
        return true;
    }

    if (cell->getTypeCell() == TypeCell::GOLD && b.type == TypeTank::ENEMY) {
        cell->setTypeCell(TypeCell::NONE);
        b.isShotMade = false;
        m->loss = true;
        m->victory = false;
        return true;
    }

    if (cell->getTypeCell() == TypeCell::GOLD && b.type == TypeTank::MAIN) {
        b.isShotMade = false;
        return true;
    }

    //If on the way at the bullet the enemy tank and the bullet of the main tank
    if (cell->getTypeCell() == TypeCell::ENEMY_TANK && b.type == TypeTank::MAIN) {
        for (size_t i = 0; i < m->enemyTanks.size(); ++i) {
            if (checkTank(b, m->enemyTanks[i], x, y)) {
                return true;
            }
        }
    }

    //If on the way at the bullet the main tank and the bullet of the enemy tank
    if (cell->getTypeCell() == TypeCell::MAIN_TANK && b.type == TypeTank::ENEMY) {
        if (checkTank(b, m->tank, x, y)) {
            return true;
        }
    }

    //If on the way at the bullet the enemy tank and the bullet of the enemy tank
    //do not replace the tank with a bullet
    if (!(cell->getTypeCell() == TypeCell::ENEMY_TANK && b.type == TypeTank::ENEMY))
        cell->setTypeCell(TypeCell::BULLET);

    return false;
}

bool BulletAction::checkTank(Bullet &b, Tank *t, int x, int y)
{
    //check in which tank to take health
    if (t->id == m->field[y][x].id) {
        //if the health are zero, we erase the tank from the field
        if (--(t->health) == 0) {
            x = t->x;
            y = t->y;
            m->field[y][x].setTypeCell(TypeCell::NONE);
            m->field[y - 1][x].setTypeCell(TypeCell::NONE);
            m->field[y + 1][x].setTypeCell(TypeCell::NONE);
            m->field[y][x - 1].setTypeCell(TypeCell::NONE);
            m->field[y][x + 1].setTypeCell(TypeCell::NONE);
            m->field[y - 1][x - 1].setTypeCell(TypeCell::NONE);
            m->field[y + 1][x - 1].setTypeCell(TypeCell::NONE);
            m->field[y + 1][x + 1].setTypeCell(TypeCell::NONE);
            m->field[y - 1][x + 1].setTypeCell(TypeCell::NONE);
        }
        b.isShotMade = false;
        return true;
    }

    return false;
}

void BulletAction::shot(Bullet &b)
{
    //bullet flight
    if (m->field.at(b.y).at(b.x).getTypeCell() == TypeCell::BULLET)
        m->field[b.y][b.x].setTypeCell(TypeCell::NONE);

    switch (b.direction) {
    case Direction::LEFT:
        if (checkIntersection(b, b.x - 1, b.y))
            return;
        --b.x;
        break;
    case Direction::RIGHT:
        if (checkIntersection(b, b.x + 1, b.y))
            return;
        ++b.x;
        break;
    case Direction::UP:
        if (checkIntersection(b, b.x, b.y - 1))
            return;
        --b.y;
        break;
    case Direction::DOWN:
        if (checkIntersection(b, b.x, b.y + 1))
            return;
        ++b.y;
        break;
    case Direction::NONE:
        break;
    }
}
