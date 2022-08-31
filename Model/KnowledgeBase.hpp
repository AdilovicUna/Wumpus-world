#pragma once

#include "WumpusWorld.hpp"

class KnowledgeBase
{
private:
    int gridSize;

    std::vector<std::vector<std::set<Element>>> grid;

    Pos agent;
    // adds an elem at the pos position to the grid
    void addElement(const Pos &pos, const Element &elem);

    // checks if we can know for certian that the position pos
    // has the wumpus or a pit
    bool mightContainObject(const Pos &pos, const Element &percept) const;

    bool perceptAtPos(const Pos &pos, const Element &percept) const;

    // gets all cells with the distance of 2 from it
    // eg. pos {4, 4}, one of the second neighbors will be {4, 2}
    std::vector<Pos> getSecondNeighbors(const Pos& pos) const;

public:
    Maps m;

    // keeps track of explored cells
    std::vector<std::vector<bool>> visited;

    KnowledgeBase(int size);

    // add some information to the KB
    void tell(Pos &pos, std::set<Element> &info);

    // check how safe it is to move to position
    Move ask(const Pos &curr, const Pos &next);

    // gets wumpus pos if it is known otherwise null
    Pos getWumpusPos();
};