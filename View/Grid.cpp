#include "Grid.hpp"

Grid::Grid(SDL_Renderer* r, int n) : size(n), renderer(r), solver(WumpusWorld(n))
{
}

void Grid::drawGrid()
{
	int squareSize = boardSize / size;
	Point curr;
	Pos agentPos = { size - 1, 0 };
	Pos wumpusPos = { -1, -1 };
	Pos goldPos = {-1, -1};

	int row = 0;
	int col = 0;
	for (int i = start.x ; i < start.x + (squareSize * size); i += squareSize)
	{
		row = 0;
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			curr = { i, j };
			agentPos = solver.world.findElement(agent);
			wumpusPos = solver.world.findElement(wumpus);
			goldPos = solver.world.findElement(gold);

			// draw agent
			if (agentPos.getRow() == row && agentPos.getCol() == col)
				fillRectangle(curr, squareSize, agentColor);
			// draw wumpus
			else if (wumpusPos.getRow() == row && wumpusPos.getCol() == col)
					fillRectangle(curr, squareSize, wumpusColor);
			// draw gold
			else if (goldPos.getRow() == row && goldPos.getCol() == col)
				fillRectangle(curr, squareSize, goldColor);
			// check if this was the selected rectangle
			else if (selected.x > i && selected.x < i + squareSize && selected.y > j && selected.y < j + squareSize)
				fillRectangle(curr, squareSize, selectedColor);
			else
				drawRectangle(curr, squareSize, color);

			row++;
		}
		col++;
	}
}

void Grid::drawRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	SDL_Rect rect = { p.x, p.y, squareSize, squareSize};
	SDL_RenderDrawRect(renderer, &rect);
}

void Grid::fillRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the filled rectangle
	SDL_Rect rect = { p.x, p.y, squareSize, squareSize };
	SDL_RenderFillRect(renderer, &rect);
}

void Grid::addImage(Point p, int squareSize, std::string &character)
{

	//image = SDL_LoadBMP("Images/agent.png");
	/*texture = IMG_LoadTexture(renderer, "Images/" + character + ".png");

	SDL_Rect rect = { p.x, p.y, squareSize, squareSize };
	SDL_RenderCopy(renderer, texture, NULL, &rect);*/

	SDL_Color color = { 25, 0, 150, SDL_ALPHA_OPAQUE }; // purple cherry

	if (character == "agent")
	{
		color = { 150, 150, 150 };
	}
	
	fillRectangle(p, squareSize, color);
}

void Grid::selectSquare(Point p)
{
	if (p.x >= start.x && p.y >= start.y && p.x <= start.x + boardSize && p.y <= start.y + boardSize)
	{
		selected = p;
	}
	else
	{
		selected = { -1, -1 }; // nothing was selected
	}
}

void Grid::addElement(SDL_Keycode key, Point p)
{
	Pos cell = getCell(selected);

	if (key == SDLK_w)
	{
		solver.world.addWumpus(cell);
	}
	else if (key == SDLK_g)
	{
		solver.world.addGold(cell);
	}
	else if (key == SDLK_p)
	{

	}
	solver.world.printGrid();
}

Pos Grid::getCell(Point p)
{
	int squareSize = boardSize / size;
	int row = 0;
	int col = 0;
	for (int i = start.x; i < start.x + (squareSize * size); i += squareSize)
	{
		col = 0;
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			// check if this was the selected rectangle
			if (p.x > i && p.x < i + squareSize && p.y > j && p.y < j + squareSize)
			{
				return Pos{ col, row };
			}
			col++;
		}
		row++;
	}
	return Pos{ -1, -1 };
}

void Grid::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
}