#include "Grid.hpp"

Grid::Grid(SDL_Renderer* &r, int n) : size(n), renderer(r), solver(WumpusWorld(n))
{
	agentImage = IMG_Load("View/Images/agent.png");
	agentArrowImage = IMG_Load("View/Images/agent_arrow.png");
	goldImage = IMG_Load("View/Images/gold.png");
	wumpusImage = IMG_Load("View/Images/wumpus.png");
	pitImage = IMG_Load("View/Images/pit.png");

	if (!agentImage || !agentArrowImage || !goldImage || !wumpusImage || !pitImage)
	{
		printf(IMG_GetError());
	}
} 

void Grid::drawGrid()
{
	int squareSize = boardSize / size;
	Point curr;

	Pos agentPos = solver.world.getAgentPos();
	Pos goldPos = solver.world.findElement(gold);
	Pos wumpusPos = solver.world.findElement(wumpus);
	std::vector<Pos> pitsPos = solver.world.findMultipleElements(pit);
	std::vector<Pos> stenchPos = solver.world.findMultipleElements(stench);
	std::vector<Pos> breezePos = solver.world.findMultipleElements(breeze);

	int row = 0;
	int col = 0;
	for (int i = start.x ; i < start.x + (squareSize * size); i += squareSize)
	{
		row = 0;
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			curr = { i, j };

			// COLORS
			// draw pairs of stench and breeze
			if (checkIfElementOnPos(stenchPos, row, col) && checkIfElementOnPos(breezePos, row, col))
				fillRectangle(curr, squareSize, outlineColor, stenchColor);

			// draw stenches
			else if (checkIfElementOnPos(stenchPos, row, col))
				fillRectangle(curr, squareSize, stenchColor);

			// draw breeezes
			else if (checkIfElementOnPos(breezePos, row, col))
				fillRectangle(curr, squareSize, breezeColor);

			// check if this was the selected rectangle
			else if (selected.x > i && selected.x < i + squareSize && selected.y > j && selected.y < j + squareSize)
				fillRectangle(curr, squareSize, selectedColor);

			// IMAGES
			// draw agent
			if (agentPos.row == row && agentPos.col == col)
				addImage(curr, squareSize, Element::agent);

			// draw gold
			else if (goldPos.row == row && goldPos.col == col)
				addImage(curr, squareSize, Element::gold);

			// draw wumpus
			else if (wumpusPos.row == row && wumpusPos.col == col)
				addImage(curr, squareSize, Element::wumpus);

			// draw pits
			else if (checkIfElementOnPos(pitsPos, row, col))
				addImage(curr, squareSize, Element::pit);

			// OUTLINE
			drawRectangle(curr, squareSize, outlineColor);

			row++;
		}
		col++;
	}
}

void Grid::play()
{
	std::cout << "inside play" << std::endl;
	playOn = true;
	Pos curr = solver.world.getAgentPos();
	for (const auto& pos : solver.pathTaken)
	{
		solver.world.moveAgent(curr, pos);
		curr = pos;
		std::cout << "forward" << std::endl;
		SDL_Delay(100);
	}

	for (int i = solver.pathTaken.size() - 1; i >= 0; i--)
	{
		solver.world.moveAgent(curr, solver.pathTaken[i]);
		curr = solver.pathTaken[i];
		std::cout << "return" << std::endl;
		SDL_Delay(100);
	}
	playOn = false;
}

bool Grid::checkIfElementOnPos(const std::vector<Pos> &elements, int row, int col) const
{
	for (const auto& elemPos : elements)
	{
		if (elemPos.row == row && elemPos.col == col)
		{
			return true;
		}
	}
	return false;
}

void Grid::drawRectangle(const Point &p, int squareSize, const SDL_Color &color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	rect = { p.x, p.y, squareSize, squareSize};
	SDL_RenderDrawRect(renderer, &rect);
}

void Grid::fillRectangle(const Point& p, int squareSize, const SDL_Color& color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the filled rectangle
	rect = { p.x, p.y, squareSize, squareSize };
	SDL_RenderFillRect(renderer, &rect);
}

void Grid::fillRectangle(const Point &p, int squareSize, const SDL_Color &color1, const SDL_Color &color2)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color1.r, color1.g, color1.b, color1.a);

	// draw the filled rectangle
	rect = { p.x, p.y, squareSize, squareSize / 2 };
	SDL_RenderFillRect(renderer, &rect);

	// set the color
	SDL_SetRenderDrawColor(renderer, color2.r, color2.g, color2.b, color2.a);

	// draw the filled rectangle
	rect = { p.x, p.y + (squareSize / 2), squareSize, squareSize / 2 };
	SDL_RenderFillRect(renderer, &rect);
}


void Grid::addImage(const Point &p, int squareSize, const Element &elem)
{
	switch (elem)
	{
	case agent:
		if (solver.world.hasArrow)
			texture = SDL_CreateTextureFromSurface(renderer, agentArrowImage);
		else
			texture = SDL_CreateTextureFromSurface(renderer, agentImage);
		break;
	case gold:
			texture = SDL_CreateTextureFromSurface(renderer, goldImage);
			break;
	case wumpus:
		texture = SDL_CreateTextureFromSurface(renderer, wumpusImage);
		break;
	case pit:
		texture = SDL_CreateTextureFromSurface(renderer, pitImage);
		break;
	}

	rect = { p.x, p.y, squareSize, squareSize };

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Grid::selectSquare(const Point &p)
{
	if (p.x >= start.x && p.y >= start.y && p.x <= start.x + boardSize && p.y <= start.y + boardSize)
	{
		selected = p;
	}
	else
	{
		selected = { -1, -1 }; // nothing was selected
	}
}

void Grid::addElement(const SDL_Keycode &key, const Point &p)
{
	Pos cell = getCell(selected);

	if (key == SDLK_w)
	{
		solver.world.addWumpus(cell);
	}
	else if (key == SDLK_g)
	{
		solver.world.addGold(cell);
	}
	else if (key == SDLK_p)
	{
		std::set<Element> cellContent = solver.world.getCell(cell);
		if (cellContent.find(pit) == cellContent.end())
			solver.world.addPit(cell);
		else
			solver.world.removePit(cell);
	}
	solver.world.printGrid();
}

Pos Grid::getCell(const Point &p) const
{
	int squareSize = boardSize / size;
	int row = 0;
	int col = 0;
	for (int i = start.x; i < start.x + (squareSize * size); i += squareSize)
	{
		col = 0;
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			// check if this was the selected rectangle
			if (p.x > i && p.x < i + squareSize && p.y > j && p.y < j + squareSize)
			{
				return Pos{ col, row };
			}
			col++;
		}
		row++;
	}
	return Pos{ -1, -1 };
}

void Grid::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	SDL_FreeSurface(agentImage);
	SDL_FreeSurface(agentArrowImage);
	SDL_FreeSurface(wumpusImage);
	SDL_FreeSurface(goldImage);
	SDL_FreeSurface(pitImage);
}