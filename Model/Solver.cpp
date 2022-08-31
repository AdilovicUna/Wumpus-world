#include "Solver.hpp"

Solver::Solver(WumpusWorld w) : world(w), KB(w.getSize()), 
    agentStartingPos({ w.getSize() - 1, 0 }),
    passed(w.getSize(), std::vector<bool>(w.getSize(), false))
{
}

bool Solver::isFinished(const std::set<Element> cell)
{
    if (isWinningPos(cell))
    {
        won();
        return true;
    }
    else if (isLoosingPos(cell))
    {
        return true;
    }
    return false;
}

void Solver::solve()
{
    Pos start = world.getAgentPos();
    pathTaken.push_back(start);
    helperSolve(start);
}

void Solver::helperSolve(Pos curr)
{
    if (done) // finished
        return;

    std::set<Element> cell = world.getCell(curr);
    passed[curr.row][curr.col] = true;

    if (isFinished(cell))
    {
        done = true;
    }
    else
    {
        KB.tell(curr, cell);

        for (const auto &neighbor : world.getNeighbors(curr))
        {
            if (passed[neighbor.row][neighbor.col])
            {
                continue;
            }
            if (KB.ask(curr, neighbor) == Move::safe)
            {
                if (!done)
                    pathTaken.push_back(neighbor);
                helperSolve(neighbor);
                if (!done)
                    pathTaken.push_back(curr);
            }
        }

        // agent has 1 arrow per game to try and shoot the wumpus down
        Pos wumpusPos = KB.getWumpusPos();

        if (world.hasArrow && wumpusPos.row != -1)
        {
            world.shoot(wumpusPos);
        }

        return;
    }
}

bool Solver::isWinningPos(const std::set<Element> &cell) const
{
    return cell.find(Element::gold) != cell.end();
}

bool Solver::isLoosingPos(const std::set<Element> &cell) const
{
    return cell.find(Element::wumpus) != cell.end() ||
           cell.find(Element::pit) != cell.end();
}

void Solver::won()
{
    goldFound = true;

    std::vector<Pos> temp;
    for (const auto &pos : pathTaken)
    {
        temp.push_back(pos);
    }

    // add reversed pathTaken as well (go back to initial pos)
    for (int i = pathTaken.size() - 2; i >= 0; i--)
    {
        temp.push_back(pathTaken[i]);

        if (agentStartingPos.row == pathTaken[i].row && agentStartingPos.col == pathTaken[i].col)
            break;
    }
    pathTaken = temp;
}