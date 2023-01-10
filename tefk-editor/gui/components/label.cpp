#include "label.hpp"

namespace tefk {

Label::Label()
	: GUIComponent{ SizeBehaviour::CONTENT }
{}

std::string Label::GetText() {
	return _text;
}

void Label::SetText(std::string text) {
	_text = text;
}

short Label::UpdateHeight() {
	short divider = _size.X == 0 ? _text.size() : _size.X;
	return _size.Y = (short)ceil(double(_text.size()) / divider);
}

void Label::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	for (size_t y = 0; y < _size.Y; y++) {
		for (size_t x = 0; x < _size.X; x++) {
			size_t charIndex = x + y * _size.X;
			bool drawEmptySpace = charIndex >= _text.size();

			Canvas::Instance().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : _text[charIndex];
			Canvas::Instance().PixelAt(x + _pos.X, y + _pos.Y).color = _color;
		}
	}
}

} // namespace tefk