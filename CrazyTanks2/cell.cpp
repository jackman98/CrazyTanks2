#include "cell.h"

Cell::Cell(TypeCell t) : strength(0), typeCell_(t)
{
    setTypeCell(t);
}

TypeCell Cell::getTypeCell() const
{
    return typeCell_;
}

std::string Cell::getCode() const
{
    return code;
}

void Cell::setTypeCell(TypeCell t)
{
    typeCell_ = t;
    switch (t) {
    case TypeCell::BOUNDARY:
        id = -1;
        code = "$";
        break;
    case TypeCell::WALL:
        id = -1;
        code = "$";
        strength = rand() % 3 + 1;
        break;
    case TypeCell::MAIN_TANK:
        id = -1;
        code = "#";
        break;
    case TypeCell::ENEMY_TANK:
        id = -1;
        code = "@";
        break;
    case TypeCell::GOLD:
        id = -1;
        code = "%";
        break;
    case TypeCell::BULLET:
        id = -1;
        code = "*";
        break;
    case TypeCell::NONE:
        id = -1;
        code = " ";
        break;
    default:
        id = -1;
        code = " ";
        break;
    }
}
