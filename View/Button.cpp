#include "Button.hpp"
#include <iostream>

Button::Button(SDL_Renderer* &r) : renderer(r)
{
	if (TTF_Init() == -1)
		printf(TTF_GetError());

	smallFont = TTF_OpenFont("View/Font/font.ttf", 50);
	bigFont = TTF_OpenFont("View/Font/font.ttf", 500);

	if (!smallFont || !bigFont)
		printf(TTF_GetError());
}

void Button::drawButton(const Point &p, int width, int height)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);

	// draw the rectangle
	rect = { p.x, p.y, width, height };
	SDL_RenderDrawRect(renderer, &rect);
}

void Button::drawButtons()
{
	if (!showHelp)
	{
		drawButton(playButton, playButtonWidth, playButtonHeight);
		drawButton(helpButton, helpButtonWidth, helpButtonHeight);

		displayText(playButton, playButtonWidth, playButtonHeight, bigFont, playButtonText);
		displayText(helpButton, helpButtonWidth, helpButtonHeight, bigFont, helpButtonText);
	}
	else
	{
		drawButton(exitHelpButton, exitHelpButtonWidth, exitHelpButtonHeight);
		displayText(exitHelpButton, exitHelpButtonWidth, exitHelpButtonHeight, bigFont, backButtonText);
		displayHelp();
	}
}

void Button::displayHelp()
{
	for (auto& line : helpText)
	{
		displayText(helpTextPos, helpWidth, helpHeight, smallFont, line);
		helpTextPos.y += helpHeight;
	}
	helpTextPos = { 150, 150 };
}

void Button::drawTitle()
{
	displayText(titlePos, titleWidth, titleHeight, bigFont, title);
}

void Button::displayText(const Point &p, int width, int height, TTF_Font* &font, const char* &text)
{
	surface = TTF_RenderText_Solid(font, text, outlineColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//int textureWidth;
	//int textureHeight;
	//SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	rect = { p.x, p.y, width, height };

	/*int textureStartRow = rect.y + 0.5 * (rect.h - textureHeight);
	const int textureStartCol = rect.x + 0.5 * (rect.w - textureWidth);

	rect = { textureStartCol, textureStartRow, textureWidth, textureHeight };*/

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Button::isPlayButtonClicked(const Point &p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > playButton.x && p.x < playButton.x + playButtonWidth
		&& p.y > playButton.y && p.y < playButton.y + playButtonHeight)
	{
		return true;
	}
	return false;
}

bool Button::isHelpButtonClicked(const Point &p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > helpButton.x && p.x < helpButton.x + helpButtonWidth
		&& p.y > helpButton.y && p.y < helpButton.y + helpButtonHeight)
	{
		return true;
	}
	return false;
}

bool Button::isExitHelpButtonClicked(const Point &p)
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

void Button::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(smallFont);
	TTF_CloseFont(bigFont);
}