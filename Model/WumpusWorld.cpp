#include "WumpusWorld.hpp"

WumpusWorld::WumpusWorld(int n)
    : size(n), grid(n, std::vector<std::set<Element>>(n, std::set<Element>()))
{
    // agent can only start at the bottom left corner
    Pos agentPos = { n - 1 , 0 };
    addElement(agentPos, agent);
}

void WumpusWorld::addWumpus(const Pos &wumpusPos)
{
    if (wumpusPos.getRow() == -1)
    {
        return;
    }

    removeWumpus();
    if (addElement(wumpusPos, wumpus))
    {
        // add stench to all wumpus neighbors
        for (const auto& pos : getNeighbors(wumpusPos))
        {
            addElement(pos, stench);
        }
    }
}

void WumpusWorld::addPit(const Pos &pitPos)
{
    if (pitPos.getRow() == -1)
    {
        return;
    }

    if (addElement(pitPos, pit)) 
    {
        // add breeze to all pit neighbors
        for (const auto& pos : getNeighbors(pitPos))
        {
            addElement(pos, breeze);
        }
    }
}

void WumpusWorld::addGold(const Pos &goldPos)
{
    if (goldPos.getRow() == -1)
    {
        return;
    }

    removeGold();
    addElement(goldPos, gold);
}

bool WumpusWorld::addElement(const Pos& pos, const Element &elem)
{
    // if we try to add more than 1 object at the same pos
    if (getLayer[elem] == object &&
        (hasObject(grid[pos.getRow()][pos.getCol()]) || 
        (pos.getRow() == size - 1 && pos.getCol() == 0)))
    {
        return false;
    }
    grid[pos.getRow()][pos.getCol()].insert(elem);

    return true;
}

void WumpusWorld::removeWumpus()
{
    Pos wumpusPos = findElement(wumpus);
    if (wumpusPos.getRow() == -1)
    {
        return;
    }

    removeElement(wumpusPos, wumpus);

    // remove stench to all wumpus neighbors
    for (const auto& pos : getNeighbors(wumpusPos))
    {
        removeElement(pos, stench);
    }
}

void WumpusWorld::removePit(const Pos &pitPos)
{
    removeElement(pitPos, pit);

    // remove breeze to all pit neighbors
    for (const auto& pos : getNeighbors(pitPos))
    {
        removeElement(pos, breeze);
    }
}

void WumpusWorld::removeGold()
{
    Pos goldPos = findElement(gold);
    if (goldPos.getRow() == -1)
    {
        return;
    }

    removeElement(goldPos, gold);
}

void WumpusWorld::removeElement(const Pos &pos, const Element &elem)
{
    grid[pos.getRow()][pos.getCol()].erase(elem);
}

std::vector<Pos> WumpusWorld::getNeighbors(const Pos &pos) const
{
    std::vector<Pos> result;
    int neighborRow[4] = {-1, 1, 0, 0};
    int neighborCol[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        Pos newPos(pos.getRow() + neighborRow[i], pos.getCol() + neighborCol[i]);
        if (0 <= newPos.getRow() && newPos.getRow() < size &&
            0 <= newPos.getCol() && newPos.getCol() < size)
        {
            result.push_back(newPos);
        }
    }
    //std::cout << "# of neighbors: " << result.size() << std::endl;
    return result;
}

bool WumpusWorld::hasObject(const std::set<Element> &cell) const
{
    for (const auto &elem : cell)
    {
        if (getLayer[elem] == object)
        {
            return true;
        }
    }
    return false;
}

Pos WumpusWorld::findElement(const Element &elem) const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (const auto& e : getCell(Pos{ i, j }))
            {
                if (elem == e)
                {
                    return Pos{ i,j };
                }
            }
        }
    }
    return Pos{ -1, -1 };
}

std::vector<Pos> WumpusWorld::findMultipleElements(const Element &elem) const
{
    std::vector<Pos> result;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (const auto& e : getCell(Pos{ i, j }))
            {
                if (elem == e)
                {
                    result.push_back(Pos{ i,j });
                }
            }
        }
    }
    return result;
}

void WumpusWorld::printGrid() const
{
    for (const auto &row : grid)
    {
        for (const auto &col : row)
        {
            std::cout << "( ";
            for (const auto &elem : col)
            {
                std::cout << getElementName[elem] << " ";
            }
            std::cout << ") ";
        }
        std::cout << std::endl;
    }
    std::cout<<"*************************"<<std::endl;
}

const std::set<Element> &WumpusWorld::getCell(const Pos &pos) const
{
    return grid[pos.getRow()][pos.getCol()];
}

int WumpusWorld::getSize() const
{
    return size;
}

void WumpusWorld::moveAgent(const Pos &prevPos, const Pos &newPos)
{
    auto iter = grid[prevPos.getRow()][prevPos.getCol()].find(agent);
    grid[prevPos.getRow()][prevPos.getCol()].erase(iter);
    grid[newPos.getRow()][newPos.getCol()].insert(agent);
}
