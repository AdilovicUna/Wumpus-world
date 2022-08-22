#include "Pos.hpp"

Pos::Pos(int row, int col) : pos(row, col)
{
}

int Pos::getRow()
{
    return pos.first;
}

int Pos::getCol()
{
    return pos.second;
}