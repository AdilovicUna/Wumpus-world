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
    int height;
    int width;

    std::vector<std::vector<std::set<Element>>> grid;

    // adds an elem at the pos position to the grid
    void addElement(Pos pos, Element elem);

    // removes an elem at the pos position to the grid
    void removeElement(Pos pos, Element elem);

    // check if cell has any element in object layer
    bool hasObject(const std::set<Element> &cell) const;


public:
    WumpusWorld(int n);

    void addWumpus(Pos wumpusPos);
    void addPit(Pos wumpusPos);
    void addGold(Pos wumpusPos);

    void removeWumpus();
    void removePit(Pos pitPos);
    void removeGold();

    // gets content of a cell at position pos
    const std::set<Element> &getCell(Pos pos) const;

    // find position of an element
    Pos findElement(Element elem) const;

    // gets all neighbor positions of pos (4 sides, if they are not walls)
    std::vector<Pos> getNeighbors(Pos pos) const;

    // moves the agent from one position to another
    void moveAgent(Pos prevPos, Pos newPos);

    int getHeight() const;
    int getWidth() const;

    void printGrid() const;
};