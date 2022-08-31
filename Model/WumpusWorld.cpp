#include "WumpusWorld.hpp"

WumpusWorld::WumpusWorld(int n)
    : size(n), grid(n, std::vector<std::set<Element>>(n, std::set<Element>()))
{
    // agent can only start at the bottom left corner
    Pos agentPos = { n - 1 , 0 };
    addElement(agentPos, Element::agent);
}

void WumpusWorld::addWumpus(const Pos &wumpusPos)
{
    if (wumpusPos.row == -1)
    {
        return;
    }

    removeWumpus();
    if (addElement(wumpusPos, Element::wumpus))
    {
        // add stench to all wumpus neighbors
        for (const auto& pos : getNeighbors(wumpusPos))
        {
            addElement(pos, Element::stench);
        }
    }
}

void WumpusWorld::addPit(const Pos &pitPos)
{
    if (pitPos.row == -1)
    {
        return;
    }

    if (addElement(pitPos, Element::pit))
    {
        // add breeze to all pit neighbors
        for (const auto& pos : getNeighbors(pitPos))
        {
            addElement(pos, Element::breeze);
        }
    }
}

void WumpusWorld::addGold(const Pos &goldPos)
{
    if (goldPos.row == -1)
    {
        return;
    }

    removeGold();
    addElement(goldPos, Element::gold);
}

bool WumpusWorld::addElement(const Pos& pos, const Element &elem)
{
    // if we try to add more than 1 object at the same pos
    if (m.getLayer(elem) == Layer::object &&
        (hasObject(grid[pos.row][pos.col]) || 
        (pos.row == size - 1 && pos.col == 0)))
    {
        return false;
    }
    grid[pos.row][pos.col].insert(elem);

    return true;
}

void WumpusWorld::removeWumpus()
{
    Pos wumpusPos = findElement(Element::wumpus);
    if (wumpusPos.row == -1)
    {
        return;
    }

    removeElement(wumpusPos, Element::wumpus);

    // remove stench to all wumpus neighbors
    for (const auto& pos : getNeighbors(wumpusPos))
    {
        removeElement(pos, Element::stench);
    }
}

void WumpusWorld::removePit(const Pos &pitPos)
{
    removeElement(pitPos, Element::pit);

    // remove breeze to all pit neighbors
    for (const auto& pos : getNeighbors(pitPos))
    {
        removeElement(pos, Element::breeze);
    }
}

void WumpusWorld::removeGold()
{
    Pos goldPos = findElement(Element::gold);
    if (goldPos.row == -1)
    {
        return;
    }

    removeElement(goldPos, Element::gold);
}

void WumpusWorld::removeElement(const Pos &pos, const Element &elem)
{
    grid[pos.row][pos.col].erase(elem);
}

std::vector<Pos> WumpusWorld::getNeighbors(const Pos &pos) const
{
    std::vector<Pos> result;
    int neighborRow[4] = {-1, 1, 0, 0};
    int neighborCol[4] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        Pos newPos{ pos.row + neighborRow[i], pos.col + neighborCol[i] };
        if (0 <= newPos.row && newPos.row < size &&
            0 <= newPos.col && newPos.col < size)
        {
            result.push_back(newPos);
        }
    }
    return result;
}

bool WumpusWorld::hasObject(const std::set<Element> &cell) const
{
    for (const auto &elem : cell)
    {
        if (m.getLayer(elem) == Layer::object)
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
                std::cout << m.getElementName(elem) << " ";
            }
            std::cout << ") ";
        }
        std::cout << std::endl;
    }
    std::cout<<"*************************"<<std::endl;
}

const std::set<Element> &WumpusWorld::getCell(const Pos &pos) const
{
    return grid[pos.row][pos.col];
}

int WumpusWorld::getSize() const
{
    return size;
}

Pos WumpusWorld::getAgentPos() const
{
    return agentPos;
}

void WumpusWorld::shoot(const Pos& possibleWumpusPos)
{
    hasArrow = false;
    auto temp = grid[possibleWumpusPos.row][possibleWumpusPos.col];
    if (temp.find(Element::wumpus) != temp.end())
        removeWumpus();
}

void WumpusWorld::moveAgent(const Pos& prevPos, const Pos& newPos)
{
    auto iter = grid[agentPos.row][agentPos.col].find(Element::agent);
    grid[agentPos.row][agentPos.col].erase(iter);
    grid[newPos.row][newPos.col].insert(Element::agent);
    agentPos = newPos;
}