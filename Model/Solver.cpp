#include "Solver.hpp"

Solver::Solver(WumpusWorld w) : world(w), KB(w.getSize())
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
        lost();
        return true;
    }
    return false;
}

void Solver::solve()
{
    Pos start = world.getAgentPos();
    pathTaken.push_back(start);
    world.printGrid();
    helperSolve(start);
}

void Solver::helperSolve(Pos curr)
{
    if (done) // finished
    {
        return;
    }

    std::set<Element> cell = world.getCell(curr);

    if (isFinished(cell))
    {
        done = true;
    }
    else
    {
        KB.tell(curr, cell);

        for (auto neighbor : world.getNeighbors(curr))
        {
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

//void Solver::helperSolve()
//{
//    world.printGrid();
//    Pos agent = world.getAgentPos();
//    std::set<Element> cell = world.getCell(agent);
//    //std::cout<<"agent: "<<agent.getCol()<<" "<<agent.getRow()<<std::endl;
//
//    if (isWinningPos(cell))
//    {
//        traceBack();
//    }
//    else if (isLoosingPos(cell))
//    {
//        losingMessage();
//    }
//    else
//    {
//        KB.tell(agent, cell);
//        Move nextMove = unsafe;
//        Pos nextPos(agent);
//        for (auto neighbor : world.getNeighbors(agent))
//        {
//            //std::cout << "neighbor: " << neighbor.getRow() << " " << neighbor.getCol() << std::endl;
//            if (KB.exploredGrid[neighbor.getRow()][neighbor.getCol()])
//            {
//                //std::cout<<"continue"<<std::endl;
//                // we already went to this cell
//                continue;
//            }
//            Move temp = KB.ask(agent, neighbor);
//            //std::cout << "ask result: " << getMoveName[temp] << std::endl;
//            if (temp > nextMove)
//            {
//                nextMove = temp;
//                nextPos = neighbor;
//            }
//            if (nextMove == safe)
//            {
//                break;
//            }
//        }
//        pathTaken.push_back(nextPos);
//        world.moveAgent(agent, nextPos);
//        helperSolve();
//    }
//}

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
    std::cout << "won" << std::endl;
}

void Solver::lost() const
{
    std::cout << "lost" << std::endl;
}