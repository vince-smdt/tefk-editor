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

void Label::DrawPixel(Coord pos, Pixel& pixel) {
	size_t chInd = pos.X + pos.Y * _size.X;
	bool drawEmptySpace = chInd >= _text.size();

	pixel.character = drawEmptySpace ? ' ' : _text[chInd];
	pixel.color = _color;
}

} // namespace tefk