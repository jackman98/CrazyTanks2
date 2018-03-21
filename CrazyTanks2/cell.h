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
    std::string getCode() const;
    TypeCell getTypeCell() const;
    void setTypeCell(TypeCell typeCell);
    int getId() const;
    void setId(int id);
    int getStrength() const;
    void setStrength(int strength);

private:
    int id_;
    int strength_;
    TypeCell typeCell_;
    std::string code_;
};

#endif // CELL_H
