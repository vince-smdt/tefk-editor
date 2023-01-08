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
	// TEMP
	_size.X = ConsoleAPI::ColCount();

	ConsoleAPI::SetTextColor(_color);

	DrawOnCanvas(GetTrueSize());
}

Coord GUIComponent::GetTrueSize() {
	Coord size;
	size.X = GetTrueSizeAxis(_size.X, ConsoleAPI::ColCount(), _pos.X);
	size.Y = GetTrueSizeAxis(_size.Y, ConsoleAPI::RowCount(), _pos.Y);
	return size;
}

short GUIComponent::GetTrueSizeAxis(short length, short containerLength, short position) {
	return (std::min)(
		length,
		(short)(std::max)(containerLength - position, 0)
	);
}

} // namespace tefk