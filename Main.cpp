#include "Model/Solver.hpp"

// height = row, width = col

int main()
{
    size_t gridH = 4;
    size_t gridW = 4;

    Pos agentPos(gridH - 1, 0);
    Pos wumpusPos(1, 0);
    Pos goldPos(1, 1);
    std::vector<Pos> pitPos = {{0, 3}, {1, 2}, {3, 2}};
    try
    {
        WumpusWorld world(gridH, gridW, agentPos, wumpusPos, goldPos, pitPos);
        Solver s(world);
        s.solve(agentPos);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Invalid object placement" << '\n';
    }
}
