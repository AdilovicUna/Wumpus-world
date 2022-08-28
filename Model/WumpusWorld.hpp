#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Pos.hpp"

enum Element
{
    agent,
    gold,
    wumpus,
    pit,
    stench,
    breeze
};
enum Layer  
{
    zero,
    object,
    percept
};

// NOTE: every cell in the grid can have at most one object but many percepts
// zero layer is reserved for the agent as they can be part of any cell
inline std::map<Element, Layer> getLayer = {{agent, zero}, {gold, object}, {wumpus, object}, {pit, object}, {stench, percept}, {breeze, percept}};

// used to make console printing more readable
inline std::map<Element, std::string> getElementName = {{agent, "a"}, {gold, "g"}, {wumpus, "w"}, {pit, "p"}, {stench, "s"}, {breeze, "b"}};

class WumpusWorld
{
private:
    int size;

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
    WumpusWorld(int n);

    void addWumpus(const Pos& wumpusPos);
    void addPit(const Pos &wumpusPos);
    void addGold(const Pos &wumpusPos);

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

    // moves the agent from one position to another
    void moveAgent(const Pos &prevPos, const Pos &newPos);

    int getSize() const;

    void printGrid() const;
};