#ifndef CELL_H
#define CELL_H
#include <string>

enum class TypeCell {
    BOUNDARY,
    WALL,
    MAIN_TANK,
    ENEMY_TANK,
    GOLD,
    BULLET,
    NONE
};

class Cell
{
public:
    Cell(TypeCell t);
    TypeCell getTypeCell() const;
    std::string getCode() const;
    void setTypeCell(TypeCell t);
    int strength;
    int id;
private:
    TypeCell typeCell_;
    std::string code;
};

#endif // CELL_H
