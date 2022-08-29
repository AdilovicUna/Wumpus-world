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
    world.printGrid();
    Pos agent = world.getAgentPos();
    std::set<Element> cell = world.getCell(agent);
    //std::cout<<"agent: "<<agent.getCol()<<" "<<agent.getRow()<<std::endl;
    std::cout << 1 << std::endl;

    if (isWinningPos(cell))
    {
        std::cout << 2 << std::endl;
        traceBack();
        return;
    }
    else if (isLoosingPos(cell))
    {
        std::cout << 3 << std::endl;
        losingMessage();
        return;
    }

    KB.tell(agent, cell);
    Move nextMove = unsafe;
    Pos nextPos(agent);
    for (auto neighbor : world.getNeighbors(agent))
    {
        //std::cout << "neighbor: " << neighbor.getRow() << " " << neighbor.getCol() << std::endl;
        //if (KB.exploredGrid[neighbor.getRow()][neighbor.getCol()])
        //{
        //    //std::cout<<"continue"<<std::endl;
        //    // we already went to this cell
        //    continue;
        //}
        //std::cout << "ask result: " << getMoveName[temp] << std::endl;
        std::cout << 4 << std::endl;

        if (KB.ask(agent, neighbor) == safe)
        {
            std::cout << 5 << std::endl;
            //pathTaken.push_back(nextPos);
            world.moveAgent(agent, nextPos);
            solve();
        }
    }
    return;
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
    /*for (auto elem : pathTaken)
    {
        std::cout << "(" << elem.getRow() << " " << elem.getCol() << ")";
    }
    std::cout << std::endl;*/
    std::cout << "won" << std::endl;
}

void Solver::losingMessage() const
{
    std::cout << "lost" << std::endl;
}