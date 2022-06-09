#pragma once

#include "KnowledgeBase.hpp"

class Solver
{
private:
    WumpusWorld world;
    KnowledgeBase KB;
    
    std::vector<Pos> pathTaken;

    // checks if agent is in the same cell as the gold
    bool isWinningPos(std::set<Element> cell) const;

    // checks if agent is in the same cell as the wumpus or a pit
    bool isLoosingPos(std::set<Element> cell) const;

    // moves the agent to the starting position using pathTaken
    void traceBack() const;

    // informs the player that the search was unsuccessful
    void losingMessage() const;
public:
    Solver(WumpusWorld w);
    void solve(Pos agent);
};