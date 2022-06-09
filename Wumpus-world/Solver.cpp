#include "Solver.hpp"

Solver::Solver(WumpusWorld w) : world(w), KB(w.getHeight(), w.getWidth())
{
}

void Solver::solve(Pos agent)
{
    world.printGrid();
    std::set<Element> cell = world.getCell(agent);
    if (isWinningPos(cell))
    {
        traceBack();
    }
    else if (isLoosingPos(cell))
    {
        losingMessage();
    }
    else
    {
        KB.tell(agent, cell);
        Move nextMove = unsafe;
        Pos nextPos(agent);
        for (auto neighbor : world.getNeighbors(agent))
        {
            std::cout << "neighbor: " << neighbor.getRow() << " " << neighbor.getCol() << std::endl;
            if (KB.exploredGrid[neighbor.getRow()][neighbor.getCol()])
            {
                // we already went to this cell
                continue;
            }
            Move temp = KB.ask(agent, neighbor);
            std::cout << "ask: " << getMoveName[temp] << std::endl;
            if (temp > nextMove)
            {
                nextMove = temp;
                nextPos = neighbor;
            }
            if (nextMove == safe)
            {
                break;
            }
        }
        world.moveAgent(agent, nextPos);
        pathTaken.push_back(nextPos);
        solve(nextPos);
    }
}

bool Solver::isWinningPos(std::set<Element> cell) const
{
    return cell.find(gold) != cell.end();
}

bool Solver::isLoosingPos(std::set<Element> cell) const
{
    return cell.find(wumpus) != cell.end() ||
           cell.find(pit) != cell.end();
    ;
}

void Solver::traceBack() const
{
    for (auto elem : pathTaken)
    {
        std::cout << "(" << elem.getRow() << " " << elem.getCol() << ")";
    }
    std::cout << std::endl;
}

void Solver::losingMessage() const
{
    std::cout << "lost" << std::endl;
}