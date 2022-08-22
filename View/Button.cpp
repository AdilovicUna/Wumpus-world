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
	drawButton(playButton, playButtonWidth, playButtonHeight);
	drawButton(helpButton, helpButtonWidth, helpButtonHeight);
}

bool Button::isPlayButtonClicked(Point p)
{
	if (p.x > playButton.x && p.x < playButton.x + playButtonWidth
		&& p.y > playButton.y && p.y < playButton.y + playButtonHeight)
	{
		return true;

	}
	return false;
}

bool Button::isHelpButtonClicked(Point p)
{
	if (p.x > helpButton.x && p.x < helpButton.x + helpButtonWidth
		&& p.y > helpButton.y && p.y < helpButton.y + helpButtonHeight)
	{
		return true;
	}
	return false;
}