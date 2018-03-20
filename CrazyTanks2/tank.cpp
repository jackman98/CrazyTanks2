#include "tank.h"


Tank::Tank(vector<vector<Cell> > &field, int x, int y, int id, TypeTank type) : x(x), y(y), id(id), type(type)
{
    //init tank
    paintTank(field, Direction::NONE);
    if (type == TypeTank::MAIN)
        health = MY_HEALTH;
    else if (type == TypeTank::ENEMY)
        health = ENEMY_HEALTH;
}

bool Tank::Tank::checkingFreePlaceBeforeTank(vector<vector<Cell> > &field, Direction direction)
{
    //symbols for checking
    TypeCell codeCell, codeCell2, codeCell3;

    //definition this symbols
    switch (direction) {
    case Direction::LEFT:
        codeCell = field.at(y).at(x - 2).getTypeCell();
        codeCell2 = field.at(y - 1).at(x - 2).getTypeCell();
        codeCell3 = field.at(y + 1).at(x - 2).getTypeCell();
        break;
    case Direction::RIGHT:
        codeCell = field.at(y).at(x + 2).getTypeCell();
        codeCell2 = field.at(y - 1).at(x + 2).getTypeCell();
        codeCell3 = field.at(y + 1).at(x + 2).getTypeCell();
        break;
    case Direction::UP:
        codeCell = field.at(y - 2).at(x).getTypeCell();
        codeCell2 = field.at(y - 2).at(x - 1).getTypeCell();
        codeCell3 = field.at(y - 2).at(x + 1).getTypeCell();
        break;
    case Direction::DOWN:
        codeCell = field.at(y + 2).at(x).getTypeCell();
        codeCell2 = field.at(y + 2).at(x - 1).getTypeCell();
        codeCell3 = field.at(y + 2).at(x + 1).getTypeCell();
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
    this->direction = direction;
}

void Tank::paintTank(vector<vector<Cell> > &field, Direction d)
{
    //clear old tank place
    TypeCell typeCell;
    if (type == TypeTank::MAIN)
        typeCell = TypeCell::MAIN_TANK;
    else if (type == TypeTank::ENEMY)
        typeCell = TypeCell::ENEMY_TANK;

    for(int i(y - 1); i <= y + 1; i++) {
        for(int j(x - 1); j <= x + 1; j++) {
            if (field.at(i).at(j).getTypeCell() == typeCell) {
                field.at(i).at(j).setTypeCell(TypeCell::NONE);
                field.at(i).at(j).id = -1;
            }
        }
    }

    //tank direction
    vector<TypeCell> turn;
    switch (d) {
    case Direction::LEFT:
        turn = { TypeCell::NONE, typeCell, typeCell,
                 typeCell, typeCell, TypeCell::NONE,
                 TypeCell::NONE, typeCell, typeCell };/////////
         x--;
        break;
    case Direction::RIGHT:
        turn = { typeCell, typeCell, TypeCell::NONE,
                 TypeCell::NONE, typeCell, typeCell,
                 typeCell, typeCell, TypeCell::NONE };
         x++;
        break;
    case Direction::UP:
        turn = { TypeCell::NONE, typeCell, TypeCell::NONE,
                 typeCell, typeCell, typeCell,
                 typeCell, TypeCell::NONE, typeCell };
        y--;
        break;
    case Direction::DOWN:
        turn = { typeCell, TypeCell::NONE, typeCell,
                 typeCell, typeCell, typeCell,
                 TypeCell::NONE, typeCell, TypeCell::NONE };
         y++;
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
    for(int i(y - 1); i <= y + 1; i++) {
        for(int j(x - 1); j <= x + 1; j++) {
            field.at(i).at(j).setTypeCell(turn[count++]);
            field.at(i).at(j).id = id;
        }
    }
}
