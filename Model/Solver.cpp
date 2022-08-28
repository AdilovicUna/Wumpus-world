#include "Solver.hpp"

Solver::Solver(WumpusWorld w) : world(w), KB(w.getSize())
{
}

bool Solver::isFinished(const std::set<Element> &cell) const
{
    if (isWinningPos(cell))
    {
        traceBack();
        return true;
    }
    else if (isLoosingPos(cell))
    {
        losingMessage();
        return true;
    }
    return false;
}

void Solver::solve()
{
    solve(Pos{ world.getSize() - 1, 0 });
}

void Solver::solve(Pos agent)
{
    world.printGrid();
    std::set<Element> cell = world.getCell(agent);
    //std::cout<<"agent: "<<agent.getCol()<<" "<<agent.getRow()<<std::endl;

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
            //std::cout << "neighbor: " << neighbor.getRow() << " " << neighbor.getCol() << std::endl;
            if (KB.exploredGrid[neighbor.getRow()][neighbor.getCol()])
            {
                //std::cout<<"continue"<<std::endl;
                // we already went to this cell
                continue;
            }
            Move temp = KB.ask(agent, neighbor);
            //std::cout << "ask result: " << getMoveName[temp] << std::endl;
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
        pathTaken.push_back(nextPos);
        world.moveAgent(agent,nextPos);
        solve(nextPos);
    }
}

bool Solver::isWinningPos(const std::set<Element> &cell) const
{
    return cell.find(gold) != cell.end();
}

bool Solver::isLoosingPos(const std::set<Element> &cell) const
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