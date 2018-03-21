#include "tank.h"


Tank::Tank(vector<vector<Cell> > &field, int x, int y, int id, Type typeTank) : x_(x), y_(y), id_(id), type_(typeTank)
{
    //init tank
    paintTank(field, Direction::NONE);
    if (typeTank == Type::MAIN)
        health_ = MY_HEALTH;
    else if (typeTank == Type::ENEMY)
        health_ = ENEMY_HEALTH;
}

int Tank::getX() const
{
    return x_;
}

void Tank::setX(int x)
{
    x_ = x;
}

int Tank::getY() const
{
    return y_;
}

void Tank::setY(int y)
{
    y_ = y;
}

int Tank::getHealth() const
{
    return health_;
}

void Tank::setHealth(int health)
{
    health_ = health;
}

int Tank::getId() const
{
    return id_;
}

void Tank::setId(int id)
{
    id_ = id;
}

Type Tank::getType() const
{
    return type_;
}

void Tank::setType(Type type)
{
    type_ = type;
}

Direction Tank::getDirection() const
{
    return direction_;
}

void Tank::setDirection(Direction direction)
{
    direction_ = direction;
}

bool Tank::Tank::checkingFreePlaceBeforeTank(vector<vector<Cell> > &field, Direction direction)
{
    //symbols for checking
    TypeCell codeCell, codeCell2, codeCell3;

    //definition this symbols
    switch (direction) {
    case Direction::LEFT:
        codeCell = field.at(y_).at(x_ - 2).getTypeCell();
        codeCell2 = field.at(y_ - 1).at(x_ - 2).getTypeCell();
        codeCell3 = field.at(y_ + 1).at(x_ - 2).getTypeCell();
        break;
    case Direction::RIGHT:
        codeCell = field.at(y_).at(x_ + 2).getTypeCell();
        codeCell2 = field.at(y_ - 1).at(x_ + 2).getTypeCell();
        codeCell3 = field.at(y_ + 1).at(x_ + 2).getTypeCell();
        break;
    case Direction::UP:
        codeCell = field.at(y_ - 2).at(x_).getTypeCell();
        codeCell2 = field.at(y_ - 2).at(x_ - 1).getTypeCell();
        codeCell3 = field.at(y_ - 2).at(x_ + 1).getTypeCell();
        break;
    case Direction::DOWN:
        codeCell = field.at(y_ + 2).at(x_).getTypeCell();
        codeCell2 = field.at(y_ + 2).at(x_ - 1).getTypeCell();
        codeCell3 = field.at(y_ + 2).at(x_ + 1).getTypeCell();
        break;
    case Direction::NONE:
        break;
    }

    vector<TypeCell> types = {TypeCell::BOUNDARY, TypeCell::ENEMY_TANK, TypeCell::MAIN_TANK, TypeCell::GOLD, TypeCell::WALL};
    //checking symbols
    if (!any_of(begin(types), end(types), [&codeCell](const TypeCell &t) {return t == codeCell;}) &&
            !any_of(begin(types), end(types), [&codeCell2](const TypeCell &t) {return t == codeCell2;}) &&
            !any_of(begin(types), end(types), [&codeCell3](const TypeCell &t) {return t == codeCell3;})) {
        //if free place
        return true;
    }

    return false;
}

void Tank::move(vector<vector<Cell> > &field, Direction direction)
{
    switch (direction) {
    case Direction::LEFT:
        if (checkingFreePlaceBeforeTank(field, Direction::LEFT)) {
            paintTank(field, Direction::LEFT);
        }
        else return;
        break;
    case Direction::RIGHT:
        if (checkingFreePlaceBeforeTank(field, Direction::RIGHT)) {
            paintTank(field, Direction::RIGHT);
        }
        else return;
        break;
    case Direction::UP:
        if (checkingFreePlaceBeforeTank(field, Direction::UP)) {
            paintTank(field, Direction::UP);
        }
        else return;
        break;
    case Direction::DOWN:
        if (checkingFreePlaceBeforeTank(field, Direction::DOWN)) {
            paintTank(field, Direction::DOWN);
        }
        else return;
        break;
    default:
        break;
    }
    this->direction_ = direction;
}

void Tank::paintTank(vector<vector<Cell> > &field, Direction direction)
{
    //clear old tank place
    TypeCell typeCell;
    if (type_ == Type::MAIN)
        typeCell = TypeCell::MAIN_TANK;
    else
        typeCell = TypeCell::ENEMY_TANK;

    for(int i(y_ - 1); i <= y_ + 1; i++) {
        for(int j(x_ - 1); j <= x_ + 1; j++) {
            if (field.at(i).at(j).getTypeCell() == typeCell) {
                field.at(i).at(j).setTypeCell(TypeCell::NONE);
                field.at(i).at(j).setId(-1);
            }
        }
    }

    //tank direction
    vector<TypeCell> turn;
    switch (direction) {
    case Direction::LEFT:
        turn = { TypeCell::NONE, typeCell, typeCell,
                 typeCell, typeCell, TypeCell::NONE,
                 TypeCell::NONE, typeCell, typeCell };/////////
         --x_;
        break;
    case Direction::RIGHT:
        turn = { typeCell, typeCell, TypeCell::NONE,
                 TypeCell::NONE, typeCell, typeCell,
                 typeCell, typeCell, TypeCell::NONE };
         ++x_;
        break;
    case Direction::UP:
        turn = { TypeCell::NONE, typeCell, TypeCell::NONE,
                 typeCell, typeCell, typeCell,
                 typeCell, TypeCell::NONE, typeCell };
        --y_;
        break;
    case Direction::DOWN:
        turn = { typeCell, TypeCell::NONE, typeCell,
                 typeCell, typeCell, typeCell,
                 TypeCell::NONE, typeCell, TypeCell::NONE };
         ++y_;
        break;
    case Direction::NONE:
        turn = { TypeCell::NONE, typeCell, TypeCell::NONE,
                 typeCell, typeCell, typeCell,
                 typeCell, TypeCell::NONE, typeCell };
        break;
    default:
        break;
    }

    //set new position on the field
    int count = 0;
    for(int i(y_ - 1); i <= y_ + 1; i++) {
        for(int j(x_ - 1); j <= x_ + 1; j++) {
            field.at(i).at(j).setTypeCell(turn[count++]);
            field.at(i).at(j).setId(id_);
        }
    }
}
