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

void TextField::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	std::string text = GetContent();

	for (size_t y = 0; y < _size.Y; y++) {
		for (size_t x = 0; x < _size.X; x++) {
			size_t charIndex = x + y * _size.X;
			bool drawEmptySpace = charIndex >= text.size();

			GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : text[charIndex];
			GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).color = _color;
		}
	}
}

} // namespace tefk