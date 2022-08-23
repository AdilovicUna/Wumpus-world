#include "Button.hpp"

Button::Button(SDL_Renderer* r) : renderer(r)
{
}

void Button::drawButton(Point p, int width, int height)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);

	// draw the rectangle
	SDL_Rect rect = { p.x, p.y, width, height };
	SDL_RenderDrawRect(renderer, &rect);
}

void Button::drawButtons()
{
	if (!showHelp)
	{
		drawButton(playButton, playButtonWidth, playButtonHeight);
		drawButton(helpButton, helpButtonWidth, helpButtonHeight);
	}
	else
	{
		drawButton(exitHelpButton, exitHelpButtonWidth, exitHelpButtonHeight);
	}
}

bool Button::isPlayButtonClicked(Point p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > playButton.x && p.x < playButton.x + playButtonWidth
		&& p.y > playButton.y && p.y < playButton.y + playButtonHeight)
	{
		return true;
	}
	return false;
}

bool Button::isHelpButtonClicked(Point p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > helpButton.x && p.x < helpButton.x + helpButtonWidth
		&& p.y > helpButton.y && p.y < helpButton.y + helpButtonHeight)
	{
		return true;
	}
	return false;
}

bool Button::isExitHelpButtonClicked(Point p)
{
	if ( showHelp // can only be clicked when help is open
		&& p.x > exitHelpButton.x && p.x < exitHelpButton.x + exitHelpButtonWidth
		&& p.y > exitHelpButton.y && p.y < exitHelpButton.y + exitHelpButtonHeight)
	{
		return true;
	}
	return false;
}

void Button::openHelp()
{
	showHelp = true;
}

void Button::closeHelp()
{
	showHelp = false;
}