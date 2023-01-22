#include "label.hpp"

namespace tefk {

Label::Label()
	: GUIComponent{ SizeBehaviour::CONTENT }
{}

void Label::SetText(std::string text) {
	_text = text;
}

std::string Label::GetContent() {
	return _text;
}

void Label::DrawPixel(short x, short y) {
	size_t charIndex = x + y * _size.X;
	bool drawEmptySpace = charIndex >= _text.size();

	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : _text[charIndex];
	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).color = _color;
}

} // namespace tefk