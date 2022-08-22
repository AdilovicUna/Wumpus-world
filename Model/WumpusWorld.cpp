#include "WumpusWorld.hpp"

WumpusWorld::WumpusWorld(int n)
    : height(n), width(n), grid(n, std::vector<std::set<Element>>(n, std::set<Element>()))
{
    // agent can only start at the bottom left corner
    Pos agentPos = { n - 1 , 0 };
    addElement(agentPos, agent);
}

void WumpusWorld::addWumpus(Pos wumpusPos)
{
    if (wumpusPos.getRow() == -1)
    {
        return;
    }

    removeWumpus();
    addElement(wumpusPos, wumpus);

    // add stench to all wumpus neighbors
    for (const auto& pos : getNeighbors(wumpusPos))
    {
        addElement(pos, stench);
    }
}

void WumpusWorld::addPit(Pos pitPos)
{
    if (pitPos.getRow() == -1)
    {
        return;
    }

    addElement(pitPos, pit);

    // add breeze to all pit neighbors
    for (const auto& pos : getNeighbors(pitPos))
    {
        addElement(pos, breeze);
    }
}

void WumpusWorld::addGold(Pos goldPos)
{
    if (goldPos.getRow() == -1)
    {
        return;
    }

    removeGold();
    addElement(goldPos, gold);
}

void WumpusWorld::addElement(Pos pos, Element elem)
{
    // if we try to add more than 1 object at the same pos
    if (getLayer[elem] == object &&
        (hasObject(grid[pos.getRow()][pos.getCol()]) || (pos.getRow() == height - 1 && pos.getCol() == 0)))

    {
        return;
    }
    grid[pos.getRow()][pos.getCol()].insert(elem);
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

void WumpusWorld::removePit(Pos pitPos)
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

void WumpusWorld::removeElement(Pos pos, Element elem)
{
    grid[pos.getRow()][pos.getCol()].erase(elem);
}

std::vector<Pos> WumpusWorld::getNeighbors(Pos pos) const
{
    std::vector<Pos> result;
    int neighborRow[4] = {-1, 1, 0, 0};
    int neighborCol[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        Pos newPos(pos.getRow() + neighborRow[i], pos.getCol() + neighborCol[i]);
        if (0 <= newPos.getRow() && newPos.getRow() < height &&
            0 <= newPos.getCol() && newPos.getCol() < width)
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

Pos WumpusWorld::findElement(Element elem) const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (const auto& e : getCell(Pos{ i, j }))
            {
                if (e == elem)
                {
                    Pos p = { i, j };
                    return p;
                }
            }
        }
    }
    return Pos{ -1, -1 };
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

const std::set<Element> &WumpusWorld::getCell(Pos pos) const
{
    return grid[pos.getRow()][pos.getCol()];
}

int WumpusWorld::getHeight() const
{
    return height;
}

int WumpusWorld::getWidth() const
{
    return width;
}

void WumpusWorld::moveAgent(Pos prevPos, Pos newPos)
{
    auto iter = grid[prevPos.getRow()][prevPos.getCol()].find(agent);
    grid[prevPos.getRow()][prevPos.getCol()].erase(iter);
    grid[newPos.getRow()][newPos.getCol()].insert(agent);
}
