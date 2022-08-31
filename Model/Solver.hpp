#pragma once

#include "KnowledgeBase.hpp"

class Solver
{
private:
    KnowledgeBase KB;

    Pos agentStartingPos;

    bool done = false;

    // checks if agent is in the same cell as the gold
    bool isWinningPos(const std::set<Element> &cell) const;

    // checks if agent is in the same cell as the wumpus or a pit
    bool isLoosingPos(const std::set<Element> &cell) const;

    void won();
    void lost() const;

    // checks if we finished the search and prints the appropriate message
    bool isFinished(const std::set<Element> cell);
    
    void helperSolve(Pos curr);

    std::vector<std::vector<bool>> passed;

public:
    WumpusWorld world;
    std::vector<Pos> pathTaken;
    bool goldFound = false;

    Solver(WumpusWorld w);
    void solve();
};


