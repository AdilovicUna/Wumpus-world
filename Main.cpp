#include "View/Grid.hpp"
#include "View/Interface.hpp"
#include <fstream>

//NOTE: height = row, width = col

void mouseEventHandler(SDL_Event event, Grid& grid, Interface& interface, Point cursorPos)
{
    if (grid.playOn)
        return;

    if (interface.isHelpButtonClicked(cursorPos)) // check if we clicked help button
        interface.openHelp();
    else if (interface.isExitHelpButtonClicked(cursorPos)) // check if we clicked exit help button
        interface.closeHelp();
    else if (interface.isPlayButtonClicked(cursorPos)) // check if we clicked play button
    {
        grid.solver.solve();
        grid.play();
    }
    else if (event.button.clicks == 2) // check if it was a double click
        grid.selectSquare(cursorPos);
}

bool eventHandler(SDL_Event event, Grid& grid, Interface& interface)
{
    if (event.type == SDL_QUIT) // x clicked
    {
        return false;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) // mouse click
    {
        mouseEventHandler(event, grid, interface, { event.button.x, event.button.y });
    }
    else if (event.type == SDL_KEYDOWN)
    {
        grid.addElement(event.key.keysym.sym, { event.button.x, event.button.y });
    }

    return true;
}

void draw(Grid& grid, Interface& interface)
{
    interface.drawTitle();

    if (!interface.showHelp)
        grid.drawGrid();

    if (!grid.playOn)
        interface.drawButtons();

    if (grid.showOutcome)
        interface.drawOutcome(grid.outcome);
}

std::string trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> splitString(std::string& str, char delim)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(trim(token));
        str.erase(0, pos + 1);
    }
    token = str.substr(0, std::string::npos);
    result.push_back(trim(token));
    return result;
}

std::vector<std::pair<std::string, std::string>> readConfig()
{
    std::string line;
    std::vector<std::pair<std::string, std::string>> vars;

    try
    {
        std::fstream MyReadFile("config.txt");

        while (std::getline(MyReadFile, line)) {
            auto splitLine = splitString(line, '=');
            vars.push_back(std::make_pair(splitLine[0], splitLine[1]));
        }

        MyReadFile.close();

        return vars;
    }
    catch (...)
    {
        return vars;
    }
}

int convert(std::string gridSize)
{
    try
    {
        // minimum grid size is 3x3
        return stoi(gridSize) >= 3 ? stoi(gridSize) : 5;
    }
    catch(...)
    {
        return 5;
    }
}


int main(int argc, char* argv[])
{
    bool terminal = false;

    auto configVars = readConfig();
    int size = 5;
    if(!configVars.empty() && configVars[0].first == "grid_size")
         size = convert(configVars[0].second);

    // TERMINAL
    if (terminal)
    {
        Pos wumpusPos{ 1, 0 };
        Pos goldPos{ 1, 1 };
        std::vector<Pos> pitPos = { {0, 3}, {1, 2}, {3, 2} };

        try
        {
            WumpusWorld world(size);
            world.addWumpus(wumpusPos);
            world.addGold(goldPos);
            for (const auto& pit : pitPos)
            {
                world.addPit(pit);
            }
            Solver s(world);
            s.solve();
            world.printGrid();
            std::cout << "path taken: ";

            for (const auto& node : s.pathTaken)
            {
                std::cout << "(" << node.row << " " << node.col << ") ";
            }
            std::string outcome = s.goldFound ? "successful" : "unsuccessful";
            std::cout << outcome << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Invalid object placement" << '\n';
        }
    }
    else
    {
        // WINDOW
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(
            "Wumpus-world",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800,
            800,
            SDL_WINDOW_OPENGL
        );

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Check that the window was successfully created
        if (window == NULL) {
            printf("Could not create window: %s\n", SDL_GetError());
            return 1;
        }

        bool running = true;
        SDL_Event event;
        Grid grid(renderer, size);
        Interface interface(renderer);

        unsigned int lastTime = 0;
        unsigned int currentTime = 0;

        // keep redrawing everything
        while (running)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (!eventHandler(event, grid, interface))
                    running = false;
            }

            // clear
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // set background color to black
            SDL_RenderClear(renderer);


            currentTime = SDL_GetTicks();

            // draw
            if (grid.playOn)
            {
                // show next step after a second
                if (currentTime > lastTime + 1000) {
                    grid.playNext();
                    lastTime = currentTime;
                }
            }

            draw(grid, interface);

            // show
            SDL_RenderPresent(renderer);

            SDL_Delay(10);
        }

        // clean
        grid.clean();
        interface.clean();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
    
    return 0;
}