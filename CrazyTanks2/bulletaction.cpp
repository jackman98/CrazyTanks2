#include "bulletaction.h"

BulletAction::BulletAction()
{
    m = &GameManager::instance();
}

//processing the intersection with tanks and walls
bool BulletAction::checkIntersection(Bullet &b, int x, int y) {
    Cell *cell = &(m->field[y][x]);
    Type bulletType = b.getType();
    if (cell->getTypeCell() == TypeCell::BOUNDARY) {
        b.setIsShotMade(false);
        return true;
    }

    if (cell->getTypeCell() == TypeCell::WALL) {
        int strength = cell->getStrength();
        if (--strength == 0) {
            cell->setTypeCell(TypeCell::NONE);
        }
        cell->setStrength(strength);
        b.setIsShotMade(false);
        return true;
    }

    if (cell->getTypeCell() == TypeCell::GOLD && bulletType == Type::ENEMY) {
        cell->setTypeCell(TypeCell::NONE);
        b.setIsShotMade(false);
        m->loss = true;
        m->victory = false;
        return true;
    }

    if (cell->getTypeCell() == TypeCell::GOLD && bulletType == Type::MAIN) {
        b.setIsShotMade(false);
        return true;
    }

    //If on the way at the bullet the enemy tank and the bullet of the main tank
    if (cell->getTypeCell() == TypeCell::ENEMY_TANK && bulletType == Type::MAIN) {
        for (size_t i = 0; i < m->enemyTanks.size(); ++i) {
            if (checkTank(b, m->enemyTanks[i], x, y)) {
                return true;
            }
        }
    }

    //If on the way at the bullet the main tank and the bullet of the enemy tank
    if (cell->getTypeCell() == TypeCell::MAIN_TANK && bulletType == Type::ENEMY) {
        if (checkTank(b, m->tank, x, y)) {
            return true;
        }
    }

    //If on the way at the bullet the enemy tank and the bullet of the enemy tank
    //do not replace the tank with a bullet
    if (!(cell->getTypeCell() == TypeCell::ENEMY_TANK && bulletType == Type::ENEMY))
        cell->setTypeCell(TypeCell::BULLET);

    return false;
}

bool BulletAction::checkTank(Bullet &b, Tank *t, int x, int y)
{
    //check in which tank to take health
    if (t->getId() == m->field[y][x].getId()) {
        int health = t->getHealth();
        //if the health are zero, we erase the tank from the field
        if (--health == 0) {
            x = t->getX();
            y = t->getY();
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
        t->setHealth(health);
        b.setIsShotMade(false);
        return true;
    }

    return false;
}

void BulletAction::shot(Bullet &b)
{
    int bulletX = b.getX();
    int bulletY = b.getY();
    //bullet flight
    if (m->field.at(bulletY).at(bulletX).getTypeCell() == TypeCell::BULLET)
        m->field[bulletY][bulletX].setTypeCell(TypeCell::NONE);

    switch (b.getDirection()) {
    case Direction::LEFT:
        if (checkIntersection(b, bulletX - 1, bulletY))
            return;
        b.setX(--bulletX);
        break;
    case Direction::RIGHT:
        if (checkIntersection(b, bulletX + 1, bulletY))
            return;
        b.setX(++bulletX);
        break;
    case Direction::UP:
        if (checkIntersection(b, bulletX, bulletY - 1))
            return;
        b.setY(--bulletY);
        break;
    case Direction::DOWN:
        if (checkIntersection(b, bulletX, bulletY + 1))
            return;
        b.setY(++bulletY);
        break;
    case Direction::NONE:
        break;
    }
}
