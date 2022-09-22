#pragma once

#include "../Model/Solver.hpp"
#include "Point.hpp"
#include <string>
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"

class Grid
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	SDL_Surface* agentImage = nullptr;
	SDL_Surface* agentArrowImage = nullptr;
	SDL_Surface* goldImage = nullptr;
	SDL_Surface* wumpusImage = nullptr;
	SDL_Surface* pitImage = nullptr;

	SDL_Rect rect = { 0, 0, 0, 0 };

	// colors
	SDL_Color outlineColor = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray
	SDL_Color selectedColor = { 25, 25, 25, SDL_ALPHA_OPAQUE }; // dark gray

	SDL_Color breezeColor = { 150, 150, 150, 150 }; // foggy
	SDL_Color stenchColor = { 20, 100, 0, SDL_ALPHA_OPAQUE }; // dark green

	// starting position and size of the grid
	Point start = { 150, 150 };
	int boardSize = 500;

	// selected square
	Point selected = { -1, -1 };

	void drawRectangle(const Point &p, int squareSize, const SDL_Color &color);
	void fillRectangle(const Point &p, int squareSize, const SDL_Color &color);
	// fills rectangle with 2 colors split horizontally
	void fillRectangle(const Point &p, int squareSize, const SDL_Color &color1, const SDL_Color &color2);

	void addImage(const Point &p, int squareSize, const Element &elem);

	// checks if any elements are at this square
	bool checkIfElementOnPos(const std::vector<Pos>& elements, int row, int col) const;

	int currPlayPos = -1;

public:
	Solver solver;

	int size;

	// currently playing the simulation
	bool playOn = false;
	bool showOutcome = false;
	const char* outcome;

	Grid(SDL_Renderer* &r, int n);

	void drawGrid();
	void selectSquare(const Point &p);
	bool addElement(const SDL_Keycode &key, const Point &p);

	// play button pressed
	void play();
	// make next step in play
	void playNext();

	Pos getCell(const Point &p) const;

	void clean();
};