#include "Pos.hpp"

Pos::Pos(int row, int col) : pos(row, col)
{
}

int Pos::getRow() const
{
    return pos.first;
}

int Pos::getCol() const
{
    return pos.second;
}