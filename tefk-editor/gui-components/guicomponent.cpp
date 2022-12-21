#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent()
	: _pos{ _ORIGIN },
	  _size{ _ORIGIN },
	  _color{ BLACK, BLACK } // TODO - set to default component color?
{}

Coord GUIComponent::GetPosition() { return _pos; }
Coord GUIComponent::GetSize() { return _size; }
TextColor GUIComponent::GetColor() { return _color; }

void GUIComponent::SetPosition(Coord pos) { _pos = pos; }
void GUIComponent::SetSize(Coord size) { _size = size; }
void GUIComponent::SetColor(TextColor color) { _color = color; }

void GUIComponent::Print() {
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