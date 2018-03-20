#include "bullet.h"

Bullet::Bullet(int x, int y, TypeTank type, Direction d) : x(x), y(y), type(type), direction(d)
{
    isShotMade = true;

    //calculation bullet start point
    switch (d) {
    case Direction::LEFT:
           this->x--;
        break;
    case Direction::RIGHT:
            this->x++;
        break;
    case Direction::UP:
            this->y--;
        break;
    case Direction::DOWN:
            this->y++;
        break;
    default:
        break;
    }
}


