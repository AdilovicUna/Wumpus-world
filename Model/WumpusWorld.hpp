#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "Pos.hpp"
#include "Maps.hpp"

class WumpusWorld
{
private:
    int size;

    Pos agentPos = { size - 1, 0 };

    std::vector<std::vector<std::set<Element>>> grid;

    // adds an elem at the pos position to the grid
    // returns false if the element was not added
    // otherwise true
    bool addElement(const Pos &pos, const Element &elem);

    // removes an elem at the pos position to the grid
    void removeElement(const Pos &pos, const Element &elem);

    // check if cell has any element in object layer
    bool hasObject(const std::set<Element> &cell) const;

public:
    Maps m;

    bool hasArrow = true;

    WumpusWorld(int n);

    void addWumpus(const Pos& wumpusPos);
    void addPit(const Pos &pitPos);
    void addGold(const Pos &goldPos);

    void removeWumpus();
    void removePit(const Pos &pitPos);
    void removeGold();

    // gets content of a cell at position pos
    const std::set<Element> &getCell(const Pos &pos) const;

    // find position of an elem
    Pos findElement(const Element &elem) const;

    // find position of all elem
    std::vector<Pos> findMultipleElements(const Element &elem) const;

    // gets all neighbor positions of pos (4 sides, if they are not walls)
    std::vector<Pos> getNeighbors(const Pos &pos) const;

    int getSize() const;

    Pos getAgentPos() const;

    void printGrid() const;

    void moveAgent(const Pos& prevPos, const Pos& newPos);

    // removes wumpus if he is at that position
    void shoot(const Pos& possibleWumpusPos);
};