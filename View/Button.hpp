#pragma once

#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>
#include "SDL_ttf.h"
#include <vector>

class Button
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	TTF_Font* smallFont = nullptr;
	TTF_Font* bigFont = nullptr;

	SDL_Rect rect = { 0, 0, 0, 0 };

	// buttons
	int playButtonHeight = 75;  
	int playButtonWidth = 200;

	int exitHelpButtonHeight = 75;
	int exitHelpButtonWidth = 200;

	int helpButtonHeight = 50;
	int helpButtonWidth = 50;

	Point playButton = { (400 + playButtonWidth) / 2 , 650 + 20 };
	Point helpButton = { 800 - helpButtonWidth - 15, 800 - helpButtonHeight - 15 };
	Point exitHelpButton = { (400 + playButtonWidth) / 2 , 650 + 20 };
	
	const char* playButtonText = "Play";
	const char* helpButtonText = "?";
	const char* backButtonText = "Back";


	// help text
	int helpHeight = 500 / 7;
	int helpWidth = 500;
	Point helpTextPos = { 150, 150 };
	std::vector<const char*> helpText{
		"To add and/or move objects",
		"double click a cell",
		"and press one of the following keys:",
		"            w - wumpus            ",
		"            g - gold            ",
		"            p - pit            ",
		"to remove a pit repeat the same process"};

	// title
	int titleHeight = 150;
	int titleWidth = 500;
	Point titlePos = { (800 - titleWidth) / 2, 0 };
	const char* title = "Wumpus world";

	SDL_Color outlineColor = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray

	void drawButton(const Point &p, int height, int width);
	void displayText(const Point &p, int width, int height, TTF_Font* &font, const char* &text);
	void displayHelp();

public:
	bool showHelp = false;

	Button(SDL_Renderer* &r);

	// draws the buttons     
	void drawButtons();

	// displays the title
	void drawTitle();

	// check button clicks
	bool isPlayButtonClicked(const Point &p);
	bool isHelpButtonClicked(const Point &p);
	bool isExitHelpButtonClicked(const Point &p);

	void openHelp();
	void closeHelp();

	void clean();
};