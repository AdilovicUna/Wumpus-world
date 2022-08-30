#pragma once

#include "KnowledgeBase.hpp"

class Solver
{
private:
    KnowledgeBase KB;
    bool done = false;

    bool goldFound = false;

    // checks if agent is in the same cell as the gold
    bool isWinningPos(const std::set<Element> &cell) const;

    // checks if agent is in the same cell as the wumpus or a pit
    bool isLoosingPos(const std::set<Element> &cell) const;

    void won();
    void lost() const;

    // checks if we finished the search and prints the appropriate message
    bool isFinished(const std::set<Element> cell);
    
    void helperSolve(Pos curr);

public:
    WumpusWorld world;
    std::vector<Pos> pathTaken;

    Solver(WumpusWorld w);
    void solve();
};


