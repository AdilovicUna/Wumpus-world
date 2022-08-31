#pragma once

#include <map>
#include <string>

enum Element
{
    agent,
    gold,
    wumpus,
    pit,
    stench,
    breeze
};
enum Layer
{
    zero,
    object,
    percept
};

enum Move { unsafe, unknown, safe };



class Maps
{
private:
    // NOTE: every cell in the grid can have at most one object but many percepts
    // zero layer is reserved for the agent as they can be part of any cell
    std::map<Element, Layer> layerMap = { {Element::agent, Layer::zero}, {Element::gold, Layer::object}, {Element::wumpus, Layer::object}, {Element::pit, Layer::object}, {Element::stench, Layer::percept}, {Element::breeze, Layer::percept} };

    // used to make console printing more readable
    std::map<Element, std::string> elementNameMap = { {Element::agent, "a"}, {Element::gold, "g"}, {Element::wumpus, "w"}, {Element::pit, "p"}, {Element::stench, "s"}, {Element::breeze, "b"} };

    // used to make console printing more readable
    std::map<Move, std::string> moveNameMap = { {Move::unsafe, "unsafe"}, {Move::unknown, "unknown"}, {Move::safe, "safe"} };

public:
    Layer getLayer(const Element& elem) const;
    std::string getElementName(const Element& elem) const;
    std::string getMoveName(const Move& move) const;
};