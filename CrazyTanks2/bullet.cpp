#include "bullet.h"

Bullet::Bullet(int x, int y, Type type, Direction direction) : x_(x), y_(y), type_(type), direction_(direction)
{
    isShotMade_ = true;

    //calculation bullet start point
    switch (direction_) {
    case Direction::LEFT:
           x_--;
        break;
    case Direction::RIGHT:
            x_++;
        break;
    case Direction::UP:
            y_--;
        break;
    case Direction::DOWN:
            y_++;
        break;
    default:
        break;
    }
}

int Bullet::getX() const
{
    return x_;
}

void Bullet::setX(int x)
{
    x_ = x;
}

int Bullet::getY() const
{
    return y_;
}

void Bullet::setY(int y)
{
    y_ = y;
}

Type Bullet::getType() const
{
    return type_;
}

void Bullet::setType(Type type)
{
    type_ = type;
}

Direction Bullet::getDirection() const
{
    return direction_;
}

void Bullet::setDirection(Direction direction)
{
    direction_ = direction;
}

bool Bullet::getIsShotMade() const
{
    return isShotMade_;
}

void Bullet::setIsShotMade(bool isShotMade)
{
    isShotMade_ = isShotMade;
}


