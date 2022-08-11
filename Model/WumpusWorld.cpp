#include "WumpusWorld.hpp"

WumpusWorld::WumpusWorld(std::size_t gridH, std::size_t gridW, Pos agentPos, Pos wumpusPos, Pos goldPos, std::vector<Pos> pitsPos)
    : height(gridH), width(gridW), grid(gridH, std::vector<std::set<Element>>(gridW, std::set<Element>()))
{
    // agent can only start at the bottom left corner
    if (agentPos.getRow() != height - 1 || agentPos.getCol() != 0)
    {
        std::cout << "constructor " << agentPos.getRow() << " " << agentPos.getCol() << std::endl;
        throw std::exception();
    }

    addElement(agentPos, agent);
    addElement(wumpusPos, wumpus);
    // add stench to all wumpus neighbors
    for (const auto &pos : getNeighbors(wumpusPos))
    {
        addElement(pos, stench);
    }
    addElement(goldPos, gold);

    for (const auto &pitPos : pitsPos)
    {
        addElement(pitPos, pit);
        // add breeze to all pit neighbors
        for (const auto &pos : getNeighbors(pitPos))
        {
            addElement(pos, breeze);
        }
    }
}

void WumpusWorld::addElement(Pos pos, Element elem)
{
    // if we try to add 2 objects in the same cell or
    // add an object to the agents starting position
    if (getLayer[elem] == object &&
        (hasObject(grid[pos.getRow()][pos.getCol()]) || (pos.getRow() == height - 1 && pos.getCol() == 0)))

    {
        std::cout << "addElem " << pos.getRow() << " " << pos.getCol() << " " << elem << std::endl;
        throw std::exception();
    }
    grid[pos.getRow()][pos.getCol()].insert(elem);
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

std::size_t WumpusWorld::getHeight() const
{
    return height;
}

std::size_t WumpusWorld::getWidth() const
{
    return width;
}

void WumpusWorld::moveAgent(Pos prevPos, Pos newPos)
{
    auto iter = grid[prevPos.getRow()][prevPos.getCol()].find(agent);
    grid[prevPos.getRow()][prevPos.getCol()].erase(iter);
    grid[newPos.getRow()][newPos.getCol()].insert(agent);
}
