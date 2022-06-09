#include "Pos.hpp"

Pos::Pos(std::size_t row, std::size_t col) : pos(row, col)
{
}

std::size_t Pos::getRow()
{
    return pos.first;
}

std::size_t Pos::getCol()
{
    return pos.second;
}