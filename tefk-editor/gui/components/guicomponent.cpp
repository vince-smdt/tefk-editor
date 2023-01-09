#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent(SizeBehaviour heightBehaviour)
	: _pos{ 0, 0 },
	  _size{ 0, 0 },
	  _color{ BLACK, WHITE },
	  _heightBehaviour{ heightBehaviour }
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

short GUIComponent::GetHeight() {
	return _size.Y;
}

SizeBehaviour GUIComponent::GetHeightBehaviour() {
	return _heightBehaviour;
}

void GUIComponent::Render() {
	// TEMP
	_size.X = ConsoleAPI::ColCount();

	ConsoleAPI::SetTextColor(_color);

	DrawOnCanvas();
}

} // namespace tefk