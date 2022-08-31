#include "KnowledgeBase.hpp"

KnowledgeBase::KnowledgeBase(int size)
    : gridSize(size), agent(Pos{ size - 1, 0 }),
    grid(size, std::vector<std::set<Element>>(size, std::set<Element>())),
    visited(size, std::vector<bool>(size, false))
{
}

void KnowledgeBase::addElement(const Pos &pos, const Element &elem)
{
    grid[pos.row][pos.col].insert(elem);
}

void KnowledgeBase::tell(Pos &pos, std::set<Element> &info)
{
    visited[pos.row][pos.col] = true;
    for(const auto &elem: info)
    {
        if(m.getLayer(elem) == Layer::percept)
        {
            addElement(pos, elem);
        }
    }
}

Move KnowledgeBase::ask(const Pos &curr, const Pos &next)
{
    Move result = Move::unknown;
    if(grid[curr.row][curr.col].empty() ||
        (!mightContainObject(next, Element::stench) && !mightContainObject(next, Element::breeze)))
    {
        result = Move::safe;
    }
    else if(mightContainObject(next, Element::stench) || mightContainObject(next, Element::breeze))
    {
        result = Move::unsafe;
    }
   
    return result;
}

bool KnowledgeBase::mightContainObject(const Pos &pos, const Element &percept) const
{
    std::vector<Pos> neighbors;
    int neighborRow[4] = {-1, 1, 0, 0};
    int neighborCol[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        // we are in the grid, we visited that cell and we know Layer::percept is not in that cell
        Pos newPos{ pos.row + neighborRow[i], pos.col + neighborCol[i] };
        if ((0 <= newPos.row && newPos.row < gridSize &&
            0 <= newPos.col && newPos.col < gridSize) &&
            visited[newPos.row][newPos.col] == true && !perceptAtPos(newPos, percept))
        {
            return false;
        }
    }
    return true;
}

bool KnowledgeBase::perceptAtPos(const Pos& pos, const Element& percept) const
{
    return grid[pos.row][pos.col].find(percept) != grid[pos.row][pos.col].end();
}

std::vector<Pos> KnowledgeBase::getSecondNeighbors(const Pos& pos) const
{
    std::vector<Pos> result;
    int neighborRow[4] = { -2, 2, 0, 0 };
    int neighborCol[4] = { 0, 0, -2, 2 };
    for (int i = 0; i < 4; i++)
    {
        Pos newPos{ pos.row + neighborRow[i], pos.col + neighborCol[i] };
        if (0 <= newPos.row && newPos.row < gridSize &&
            0 <= newPos.col && newPos.col < gridSize)
        {
            result.push_back(newPos);
        }
    }
    return result;
}

Pos KnowledgeBase::getWumpusPos()
{
    // search for stench
    // as soon as we find it, check second neighbors
    // if there is a stench in one of those
    // wumpus must be in the cell between them
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            for (const auto& elem : grid[i][j])
            {
                if (elem == Element::stench)
                {
                    for (const auto& neighbor : getSecondNeighbors({ i, j }))
                    {
                        if (perceptAtPos(neighbor, Element::stench))
                        {
                            if (i == neighbor.row)
                                return { i, abs(j - neighbor.col) };
                            else
                                return { abs(i - neighbor.row), j };
                        }
                    }
                    return { -1, -1 };
                }
            }
        }
    }
    return { -1, -1 };
}
