#pragma once

#include <utility>
#include <vector>

class Pos
{
private:
	std::pair<int, int> pos;

public:
	Pos(int, int);

	int getRow();
	int getCol();
};