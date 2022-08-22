#pragma once

#include "../Model/Solver.hpp"
#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <string>

class Grid
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Surface* image = nullptr;
	SDL_Texture* texture = nullptr;

	// colors
	SDL_Color color = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray
	SDL_Color selectedColor = { 25, 25, 25, SDL_ALPHA_OPAQUE }; // gark gray
	SDL_Color agentColor = { 255, 255, 255, SDL_ALPHA_OPAQUE }; // white
	SDL_Color wumpusColor = { 0, 150, 0, SDL_ALPHA_OPAQUE }; // green
	SDL_Color goldColor = { 150, 150, 0, SDL_ALPHA_OPAQUE }; // yellow

	// starting position and size of the grid
	Point start = { 150, 150 };
	int boardSize = 500;

	// selected square
	Point selected = { -1, -1 };

	void drawRectangle(Point p, int squareSize, SDL_Color color);
	void fillRectangle(Point p, int squareSize, SDL_Color color);
	void addImage(Point p, int squareSize, std::string& character);

public:
	Solver solver;

	int size;

	Grid(SDL_Renderer* r, int n);

	void drawGrid();
	void selectSquare(Point p);
	void addElement(SDL_Keycode key, Point p);

	Pos getCell(Point p);

	void clean();
};