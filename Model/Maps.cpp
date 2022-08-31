#include "Maps.hpp"

Layer Maps::getLayer(const Element& elem) const
{
	return layerMap.find(elem)->second;
}

std::string Maps::getElementName(const Element& elem) const
{
	return elementNameMap.find(elem)->second;
}

std::string Maps::getMoveName(const Move& move) const
{
	return moveNameMap.find(move)->second;
}