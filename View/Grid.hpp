#pragma once

#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>

class Grid
{
public:
	int size;

	Grid(SDL_Renderer* r, int n);

	void drawGrid();
	void selectSquare(Point p);

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;

	// starting position and size of the grid
	Point start = { 150, 150 };
	int boardSize = 500;

	// selected square
	Point selected = { -1, -1 };

	void drawRectangle(Point p, int squareSize, SDL_Color color);
	void fillRectangle(Point p, int squareSize, SDL_Color color);
};