#include "View/Grid.hpp"
#include "View/Button.hpp"

//NOTE: height = row, width = col

void mouseEventHandler(SDL_Event event, Grid& grid, Button& buttons, Point cursorPos)
{
    if (buttons.isHelpButtonClicked(cursorPos)) // check if we clicked help button
        buttons.openHelp();
    else if (buttons.isExitHelpButtonClicked(cursorPos)) // check if we clicked exit help button
        buttons.closeHelp();
    else if (buttons.isPlayButtonClicked(cursorPos)) // check if we clicked play button
    {
        std::cout << "play" << std::endl;
        //grid.solver.solve();
    }
    else if (event.button.clicks == 2) // check if it was a double click
        grid.selectSquare(cursorPos);
}

bool eventHandler(SDL_Event event, Grid& grid, Button& buttons)
{
    if (event.type == SDL_QUIT) // x clicked
    {
        return false;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) // mouse click
    {
        mouseEventHandler(event, grid, buttons, { event.button.x, event.button.y });
    }
    else if (event.type == SDL_KEYDOWN)
    {
        grid.addElement(event.key.keysym.sym, { event.button.x, event.button.y });
    }

    return true;
}

void draw(Grid& grid, Button& buttons)
{
    grid.drawTitle();

    if (!buttons.showHelp)
    {
        grid.drawGrid();
    }

    buttons.drawButtons();
}

int main(int argc, char* argv[])
{
    int size = 4;
    
    // TERMINAL
   /* Pos wumpusPos(1, 0);
    Pos goldPos(1, 1);
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
        std::cout << "end" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid object placement" << '\n';
    }*/

    // WINDOW

    SDL_Window *window = nullptr;
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
    Button buttons(renderer);

    // keep redrawing everything
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (!eventHandler(event, grid, buttons))
                running = false;
        }

        // clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // set background color to black
        SDL_RenderClear(renderer);

        // draw
        draw(grid, buttons);

        // show
        SDL_RenderPresent(renderer);
    }

    // clean
    grid.clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
