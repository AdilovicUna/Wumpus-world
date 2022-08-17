#include "Grid.hpp"

Grid::Grid(SDL_Renderer* r, size_t n) : size(n), renderer(r)
{
}

void Grid::drawGrid()
{
	Point start = { 150, 150 };
	int boardSize = 500;

	int squareSize = boardSize / size;
	Point curr;

	for (int i = start.x ; i < start.x + (squareSize * size); i += squareSize)
	{
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			curr = { i, j };
			drawRectangle(curr, squareSize);
		}
	}
}

void Grid::drawRectangle(Point p, int squareSize)
{
	// set the color (light gray)
	SDL_Color color = { 200, 200, 200, SDL_ALPHA_OPAQUE };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	SDL_Rect rectToDraw = { p.x,p.y,squareSize,squareSize };
	SDL_RenderDrawRect(renderer, &rectToDraw);
}
