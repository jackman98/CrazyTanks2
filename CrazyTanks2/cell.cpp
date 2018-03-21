#include "cell.h"

Cell::Cell(TypeCell t) : strength_(0), typeCell_(t)
{
    setTypeCell(typeCell_);
}

TypeCell Cell::getTypeCell() const
{
    return typeCell_;
}

std::string Cell::getCode() const
{
    return code_;
}

void Cell::setTypeCell(TypeCell typeCell)
{
    typeCell_ = typeCell;
    switch (typeCell) {
    case TypeCell::BOUNDARY:
        id_ = -1;
        code_ = "$";
        break;
    case TypeCell::WALL:
        id_ = -1;
        code_ = "$";
        strength_ = rand() % 3 + 1;
        break;
    case TypeCell::MAIN_TANK:
        id_ = -1;
        code_ = "#";
        break;
    case TypeCell::ENEMY_TANK:
        id_ = -1;
        code_ = "@";
        break;
    case TypeCell::GOLD:
        id_ = -1;
        code_ = "%";
        break;
    case TypeCell::BULLET:
        id_ = -1;
        code_ = "*";
        break;
    case TypeCell::NONE:
        id_ = -1;
        code_ = " ";
        break;
    default:
        id_ = -1;
        code_ = " ";
        break;
    }
}

int Cell::getId() const
{
    return id_;
}

void Cell::setId(int id)
{
    id_ = id;
}

int Cell::getStrength() const
{
    return strength_;
}

void Cell::setStrength(int strength)
{
    strength_ = strength;
}
