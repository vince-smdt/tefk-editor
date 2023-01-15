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

short TextField::UpdateHeight() {
	std::string text = _label + ": " + _input;
	short divider = _size.X == 0 ? text.size() : _size.X;
	return _size.Y = (short)ceil(double(text.size()) / divider);
}

void TextField::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	std::string text = _label + ": " + _input;

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