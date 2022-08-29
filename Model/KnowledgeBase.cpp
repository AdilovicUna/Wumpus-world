#include "KnowledgeBase.hpp"

KnowledgeBase::KnowledgeBase(int size)
    : gridSize(size), agent(Pos(size - 1, 0)),
    grid(size, std::vector<std::set<Element>>(size, std::set<Element>())),
    exploredGrid(size, std::vector<bool>(size))
{
}

void KnowledgeBase::addElement(const Pos &pos, const Element &elem)
{
    grid[pos.getRow()][pos.getCol()].insert(elem);
}

void KnowledgeBase::tell(Pos &pos, std::set<Element> &info)
{
    exploredGrid[pos.getRow()][pos.getCol()] = true;
    for(const auto &elem: info)
    {
        if(getLayer[elem] == percept)
        {
            addElement(pos, elem);
        }
    }
}

Move KnowledgeBase::ask(const Pos &curr, const Pos &next) const
{
    if(grid[curr.getRow()][curr.getCol()].empty()) // agent is only in this cell
    {
        return safe;
    }
    else if(objectAtPos(next, stench) || objectAtPos(next, breeze))
    {
        return unsafe;
    }
    else
    {
        return unknown;
    }
}

bool KnowledgeBase::objectAtPos(const Pos &pos, const Element &percept) const
{
    std::vector<Pos> neighbors;
    int neighborRow[4] = {-1, 1, 0, 0};
    int neighborCol[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        Pos newPos(pos.getRow() + neighborRow[i], pos.getCol() + neighborCol[i]);
        if ((0 <= newPos.getRow() && newPos.getRow() < gridSize &&
            0 <= newPos.getCol() && newPos.getCol() < gridSize) &&
            !perceptAtPos(pos, percept))
        {
            return false;
        }
    }
    return true;
}

bool KnowledgeBase::perceptAtPos(const Pos& pos, const Element& percept) const
{
    return grid[pos.getRow()][pos.getCol()].find(percept) != grid[pos.getRow()][pos.getCol()].end();
}

