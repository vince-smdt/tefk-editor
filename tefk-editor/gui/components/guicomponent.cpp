#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent()
	: _pos{ 0, 0 },
	  _size{ 0, 0 },
	  _color{ BLACK, WHITE } // TODO - set to default color?
{}

GUIComponent::GUIComponent(Coord pos, Coord size, TextColor color)
	: _pos{ pos },
	  _size{ size },
	  _color{ color }
{}

void GUIComponent::SetPosition(Coord pos) { 
	_pos = pos;
}

void GUIComponent::SetHeight(short height) {
	_size.Y = height;
}

void GUIComponent::SetColor(TextColor color) { 
	_color = color; 
}

void GUIComponent::Print() {
	_size.X = ConsoleAPI::ColCount();

	if (RowSize() == 0)
		return;
	
	ConsoleAPI::SetTextColor(_color);

	PrintContent();
}

short GUIComponent::RowSize() {
	short size = (std::min)(
		_size.X,
		(short)(ConsoleAPI::ColCount() - _pos.X)
	);
	return (size < 0) ? 0 : size;
}

}