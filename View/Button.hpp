#pragma once

#include "Point.hpp"
#include "SDL.h"
#include <stdio.h>

class Button
{
private:
	SDL_Renderer* renderer = nullptr;

	int playButtonHeight = 75;
	int playButtonWidth = 200;

	int exitHelpButtonHeight = 75;
	int exitHelpButtonWidth = 200;

	int helpButtonHeight = 50;
	int helpButtonWidth = 50;

	Point playButton = { (400 + playButtonWidth) / 2 , 650 + 20 };
	Point helpButton = { 800 - helpButtonWidth - 15, 800 - helpButtonHeight - 15 };
	Point exitHelpButton = { (400 + playButtonWidth) / 2 , 650 + 20 };

	SDL_Color outlineColor = { 200, 200, 200, SDL_ALPHA_OPAQUE }; // light gray

	void drawButton(Point p, int height, int width);

public:
	bool showHelp = false;

	Button(SDL_Renderer* r);

	// draws the buttons
	void drawButtons();

	// check button clicks
	bool isPlayButtonClicked(Point p);
	bool isHelpButtonClicked(Point p);
	bool isExitHelpButtonClicked(Point p);

	void openHelp();
	void closeHelp();
};