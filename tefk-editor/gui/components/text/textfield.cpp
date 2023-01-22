#include "textfield.hpp"

namespace tefk {

TextField::TextField()
	: GUIComponent{ SizeBehaviour::CONTENT }
{}

std::string TextField::GetLabel() {
	return _label;
}

void TextField::SetLabel(std::string label) {
	_label = label;
}

std::string TextField::GetContent() {
	return _label + ": " + _input;
}

void TextField::DrawPixel(short x, short y) {
	std::string text = GetContent(); // TODO - optimize so we don't have to get content everytime

	size_t charIndex = x + y * _size.X;
	bool drawEmptySpace = charIndex >= text.size();

	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : text[charIndex];
	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).color = _color;
}

} // namespace tefk