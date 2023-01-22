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

void TextField::DrawPixel(Coord pos, Pixel* pixel) {
	std::string text = GetContent(); // TODO - optimize so we don't have to get content everytime

	size_t chInd = pos.X + pos.Y * _size.X;
	bool drawEmptySpace = chInd >= text.size();

	pixel->character = drawEmptySpace ? ' ' : text[chInd];
	pixel->color = _color;
}

} // namespace tefk