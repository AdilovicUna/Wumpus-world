#include "Grid.hpp"

Grid::Grid(SDL_Renderer* r, int n) : size(n), renderer(r)
{
}

void Grid::drawGrid()
{

	int squareSize = boardSize / size;
	Point curr;

	SDL_Color color = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray
	SDL_Color selectedColor = { 25, 25, 25, SDL_ALPHA_OPAQUE }; // gark gray

	for (int i = start.x ; i < start.x + (squareSize * size); i += squareSize)
	{
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			curr = { i, j };

			// check if this was the selected rectangle
			if (selected.x > i && selected.x < i + squareSize && selected.y > j && selected.y < j + squareSize)
				fillRectangle(curr, squareSize, selectedColor);
			
			drawRectangle(curr, squareSize, color);
		}
	}
}

void Grid::drawRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	SDL_Rect rectToDraw = { p.x, p.y, squareSize,squareSize};
	SDL_RenderDrawRect(renderer, &rectToDraw);
}

void Grid::fillRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	SDL_Rect rectToDraw = { p.x, p.y, squareSize,squareSize };
	SDL_RenderFillRect(renderer, &rectToDraw);
}

void Grid::selectSquare(Point p)
{
	if (p.x >= start.x && p.y >= start.y && p.x <= start.x + boardSize && p.y <= start.y + boardSize)
	{
		selected = p;
	}
	else
	{
		selected = { -1, -1 };
	}
}