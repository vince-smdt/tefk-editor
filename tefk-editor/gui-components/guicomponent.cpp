#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent()
	: _pos{ 0, 0 },
	  _size{ 0, 0 },
	  _color{ BLACK, BLACK }, // TODO - set to default component color?
	  _dynamicPositionSetter{ nullptr },
	  _dynamicSizeSetter{ nullptr },
	  _dynamicColorSetter{ nullptr }
{}

Coord GUIComponent::GetPosition() { 
	return _pos; 
}

Coord GUIComponent::GetSize() { 
	return _size; 
}

TextColor GUIComponent::GetColor() { 
	return _color;
}

void GUIComponent::SetPosition(Coord pos) { 
	_pos = pos; 
}

void GUIComponent::SetSize(Coord size) {
	_size = size; 
}

void GUIComponent::SetColor(TextColor color) { 
	_color = color; 
}

void GUIComponent::SetDynamicPosition(std::function<Coord(void)> func) {
	_dynamicPositionSetter = func;
}

void GUIComponent::SetDynamicSize(std::function<Coord(void)> func) {
	_dynamicSizeSetter = func;
}

void GUIComponent::SetDynamicColor(std::function<TextColor(void)> func) {
	_dynamicColorSetter = func;
}

void GUIComponent::Print() {
	if (_dynamicPositionSetter)
		_pos = _dynamicPositionSetter();

	if (_dynamicSizeSetter)
		_size = _dynamicSizeSetter();

	if (_dynamicColorSetter)
		_color = _dynamicColorSetter();

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