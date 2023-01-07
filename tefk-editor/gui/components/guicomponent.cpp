#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent()
	: _pos{ 0, 0 },
	  _size{ 0, 0 },
	  _color{ BLACK, WHITE }
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

void GUIComponent::Render() {
	// Set component size
	_size.X = ConsoleAPI::ColCount();

	if (RowSize() == 0)
		return;
	
	ConsoleAPI::SetTextColor(_color);

	DrawOnCanvas();
}

short GUIComponent::RowSize() {
	short size = (std::min)(
		_size.X,
		(short)(ConsoleAPI::ColCount() - _pos.X)
	);
	return (size < 0) ? 0 : size;
}

} // namespace tefk