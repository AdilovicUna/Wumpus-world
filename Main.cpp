#include "Model/Solver.hpp"
#include "View/Grid.hpp"



//NOTE: height = row, width = col

int main(int argc, char* argv[])
{
    int size = 5;

    //Pos agentPos(gridH - 1, 0);
    //Pos wumpusPos(1, 0);
    //Pos goldPos(1, 1);
    //std::vector<Pos> pitPos = {{0, 3}, {1, 2}, {3, 2}};
    //try
    //{
    //    WumpusWorld world(gridH, gridW, agentPos, wumpusPos, goldPos, pitPos);
    //    Solver s(world);
    //    s.solve(agentPos);
    //}
    //catch (const std::exception &e)
    //{
    //    std::cerr << "Invalid object placement" << '\n';
    //}

    
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

    // keep redrawing everything
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) // x clicked
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) // mouse click
            {
                if (event.button.clicks == 2) // check if it was a double click
                {
                    Point p = { event.button.x, event.button.y };
                    grid.selectSquare(p);
                }
            }
        }

        // clear
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // set background color to black
        SDL_RenderClear(renderer);

        // draw
        grid.drawGrid();

        // show
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}