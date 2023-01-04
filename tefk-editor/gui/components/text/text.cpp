#include "text.hpp"

namespace tefk {

Text::Text()
	: GUIComponent{}
{}

Text::Text(Coord pos, Coord size, TextColor color)
	: GUIComponent{ pos, size, color }
{}

}