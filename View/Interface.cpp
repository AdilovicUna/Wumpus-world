#include "Interface.hpp"

Interface::Interface(SDL_Renderer* &r) : renderer(r)
{
	if (TTF_Init() == -1)
		printf(TTF_GetError());

	smallFont = TTF_OpenFont("View/Font/font.ttf", 50);
	bigFont = TTF_OpenFont("View/Font/font.ttf", 500);

	if (!smallFont || !bigFont)
		printf(TTF_GetError());
}

void Interface::drawButton(const Point &p, int width, int height)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);

	// draw the rectangle
	rect = { p.x, p.y, width, height };
	SDL_RenderDrawRect(renderer, &rect);
}

void Interface::drawButtons()
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

void Interface::displayHelp()
{
	for (auto& line : helpText)
	{
		displayText(helpTextPos, helpWidth, helpHeight, smallFont, line);
		helpTextPos.y += helpHeight;
	}
	helpTextPos = { 150, 150 };
}

void Interface::drawTitle()
{
	displayText(titlePos, titleWidth, titleHeight, bigFont, title);
}

void Interface::drawOutcome(const char* &outcome)
{
	displayText(outcomeTextPos, outcomeWidth, outcomeHeight, bigFont, outcome);
}

void Interface::displayText(const Point &p, int width, int height, TTF_Font* &font, const char* &text)
{
	surface = TTF_RenderText_Solid(font, text, outlineColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	rect = { p.x, p.y, width, height };

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Interface::isPlayButtonClicked(const Point &p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > playButton.x && p.x < playButton.x + playButtonWidth
		&& p.y > playButton.y && p.y < playButton.y + playButtonHeight)
	{
		return true;
	}
	return false;
}

bool Interface::isHelpButtonClicked(const Point &p)
{
	if (!showHelp // cannot be clicked when help is open
		&& p.x > helpButton.x && p.x < helpButton.x + helpButtonWidth
		&& p.y > helpButton.y && p.y < helpButton.y + helpButtonHeight)
	{
		return true;
	}
	return false;
}

bool Interface::isExitHelpButtonClicked(const Point &p)
{
	if ( showHelp // can only be clicked when help is open
		&& p.x > exitHelpButton.x && p.x < exitHelpButton.x + exitHelpButtonWidth
		&& p.y > exitHelpButton.y && p.y < exitHelpButton.y + exitHelpButtonHeight)
	{
		return true;
	}
	return false;
}

void Interface::openHelp()
{
	showHelp = true;
}

void Interface::closeHelp()
{
	showHelp = false;
}

void Interface::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(smallFont);
	TTF_CloseFont(bigFont);
}