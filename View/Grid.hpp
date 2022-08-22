#pragma once

#include "../Model/Solver.hpp"
#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"
#include <string>

class Grid
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Surface* image = nullptr;
	SDL_Texture* texture = nullptr;

	// colors
	SDL_Color outlineColor = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray
	SDL_Color selectedColor = { 25, 25, 25, SDL_ALPHA_OPAQUE }; // gark gray
	SDL_Color agentColor = { 255, 255, 255, SDL_ALPHA_OPAQUE }; // white
	SDL_Color wumpusColor = { 0, 150, 0, SDL_ALPHA_OPAQUE }; // green
	SDL_Color goldColor = { 180, 150, 0, SDL_ALPHA_OPAQUE }; // yellow
	SDL_Color pitColor = { 120, 0, 150, SDL_ALPHA_OPAQUE }; // cherry

	// starting position and size of the grid
	Point start = { 150, 150 };
	int boardSize = 500;

	// selected square
	Point selected = { -1, -1 };

	void drawRectangle(Point p, int squareSize, SDL_Color color);
	void fillRectangle(Point p, int squareSize, SDL_Color color);
	void addImage(Point p, int squareSize);

	// checks if any elements are at this square
	bool checkIfElement(const std::vector<Pos>& elements, int row, int col) const;

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