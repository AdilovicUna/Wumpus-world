#pragma once

#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>

class Grid
{
public:
	size_t size;
	Grid(SDL_Renderer* r, size_t n);
	void drawGrid();
private:
	SDL_Renderer* renderer = nullptr;
	void drawRectangle(Point p, int squareSize);
};