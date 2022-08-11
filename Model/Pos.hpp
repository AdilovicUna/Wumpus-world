#pragma once

#include <utility>
#include <vector>

class Pos
{
private:
	std::pair<std::size_t, std::size_t> pos;

public:
	Pos(std::size_t row, std::size_t col);

	std::size_t getRow();
	std::size_t getCol();
};