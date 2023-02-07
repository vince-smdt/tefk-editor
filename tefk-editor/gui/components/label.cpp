#include "label.hpp"

namespace tefk {

Label::Label()
	: GUIComponent{}
{}

void Label::SetText(TefkString text) {
	_text = text;
}

TefkString Label::GetContent() {
	return _text;
}

void Label::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	for (size_t y = 0; y < _size.Y; y++) {
		for (size_t x = 0; x < _size.X; x++) {
			size_t charIndex = x + y * _size.X;
			bool drawEmptySpace = charIndex >= _text.size();

			GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : _text[charIndex];
			GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).color = _color;
		}
	}
}

} // namespace tefk