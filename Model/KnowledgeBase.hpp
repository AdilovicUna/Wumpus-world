#pragma once

#include "WumpusWorld.hpp"

enum Move {unsafe, unknown, safe};

// used to make console printing more readable
inline std::map<Move, std::string> getMoveName = {{unsafe, "unsafe"}, {unknown, "unknown"}, {safe, "safe"}};

class KnowledgeBase
{
    std::size_t gridHeight;
    std::size_t gridWidth;
    std::vector<std::vector<std::set<Element>>> grid;
    Pos agent;
    // adds an elem at the pos position to the grid
    void addElement(const Pos &pos, const Element &elem);

    // checks if we can know for certian that the position pos
    // has a stench or a breeze
    bool objectAtPos(const Pos &pos, const Element &percept) const;

    bool perceptAtPos(const Pos &pos, const Element &percept) const;
public:
    // keeps track of explored cells
    std::vector<std::vector<bool>> exploredGrid;

    KnowledgeBase(std::size_t gridH, std::size_t gridW);

    // add some information to the KB
    void tell(Pos &pos, std::set<Element> &info);

    // check how safe it is to move to position
    Move ask(const Pos &curr, const Pos &next) const;
};