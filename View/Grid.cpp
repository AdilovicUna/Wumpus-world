#include "Grid.hpp"

Grid::Grid(SDL_Renderer* r, int n) : size(n), renderer(r), solver(WumpusWorld(n))
{
	if (TTF_Init() == -1)
	{
		std::cout << "blah" << std::endl;
	}
	font = TTF_OpenFont("Font/font.ttf", 25);
	if (font == NULL)
	{
		std::cout << "blahblah" << std::endl;
	}
} 

void Grid::drawGrid()
{
	int squareSize = boardSize / size;
	Point curr;

	Pos agentPos = solver.world.findElement(agent);
	Pos goldPos = solver.world.findElement(gold);
	Pos wumpusPos = solver.world.findElement(wumpus);
	std::vector<Pos> stenchPos = solver.world.findMultipleElements(stench);
	std::vector<Pos> pitsPos = solver.world.findMultipleElements(pit);
	std::vector<Pos> breezePos = solver.world.findMultipleElements(breeze);

	int row = 0;
	int col = 0;
	for (int i = start.x ; i < start.x + (squareSize * size); i += squareSize)
	{
		row = 0;
		for (int j = start.y; j < start.y + (squareSize * size); j += squareSize)
		{
			curr = { i, j };

			// draw agent
			if (agentPos.getRow() == row && agentPos.getCol() == col)
				fillRectangle(curr, squareSize, agentColor);

			// draw gold
			else if (goldPos.getRow() == row && goldPos.getCol() == col)
				fillRectangle(curr, squareSize, goldColor);

			// draw wumpus
			else if (wumpusPos.getRow() == row && wumpusPos.getCol() == col)
				fillRectangle(curr, squareSize, wumpusColor);

			//// draw stenches
			//else if (goldPos.getRow() == row && goldPos.getCol() == col)
			//	fillRectangle(curr, squareSize, goldColor);
			
			// draw pits
			else if (checkIfElement(pitsPos, row, col))
				fillRectangle(curr, squareSize, pitColor);

			//// draw breeezes
			//else if (goldPos.getRow() == row && goldPos.getCol() == col)
			//	fillRectangle(curr, squareSize, goldColor);
			
			// check if this was the selected rectangle
			else if (selected.x > i && selected.x < i + squareSize && selected.y > j && selected.y < j + squareSize)
				fillRectangle(curr, squareSize, selectedColor);

			else
				drawRectangle(curr, squareSize, outlineColor);

			row++;
		}
		col++;
	}
}

bool Grid::checkIfElement(const std::vector<Pos> &elements, int row, int col) const
{
	for (const auto& elemPos : elements)
	{
		if (elemPos.getRow() == row && elemPos.getCol() == col)
		{
			return true;
		}
	}
	return false;
}

void Grid::drawRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the rectangle
	SDL_Rect rect = { p.x, p.y, squareSize, squareSize};
	SDL_RenderDrawRect(renderer, &rect);

	
}

void Grid::fillRectangle(Point p, int squareSize, SDL_Color color)
{
	// set the color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw the filled rectangle
	SDL_Rect rect = { p.x, p.y, squareSize, squareSize };
	SDL_RenderFillRect(renderer, &rect);
}

void Grid::addImage(Point p, int squareSize)
{

	/*image = IMG_Load("Images/rand.jpg");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);*/


	SDL_Color color = { 0, 0, 150, SDL_ALPHA_OPAQUE };
	surface = TTF_RenderText_Solid(font, "Lalalala", color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//SDL_SetRenderDrawColor(renderer, agentColor.r, agentColor.g, agentColor.b, agentColor.a);
	//SDL_Rect rect = { p.x, p.y, squareSize, squareSize };
	//SDL_RenderFillRect(renderer, &rect);

	//int textureWidth;
	//int textureHeight;
	//SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	//const int textureStartRow = rect.y + 0.5 * (rect.h - textureHeight);
	//const int textureStartCol = rect.x + 0.5 * (rect.w - textureWidth);

	//SDL_Rect trect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
	SDL_Rect trect = { 100, 100, 100, 100 };

	SDL_RenderCopy(renderer, texture, nullptr, &trect);
}

void Grid::selectSquare(Point p)
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

void Grid::addElement(SDL_Keycode key, Point p)
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

Pos Grid::getCell(Point p)
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
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}