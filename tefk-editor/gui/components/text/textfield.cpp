#include "textfield.hpp"

namespace tefk {

TextField::TextField()
	: Text{}
{}

TefkString TextField::GetLabel() {
	return _label;
}

void TextField::SetLabel(TefkString label) {
	_label = label;
}

TefkString TextField::GetContent() {
	return _label + ": " + GetText();
}

bool TextField::CatchEventFromBaseComponent(Event event) {
	// TODO - catch event and do something with it
	bool eventCaught = true;
	eventCaught = false;
	return eventCaught;
}

void TextField::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	TefkString text = GetContent();

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