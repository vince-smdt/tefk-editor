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

void TextField::GetPixelVector(PixelVector& pixelVec) {
	TefkString formatLabel = _label + ": ";
	size_t availableEmptySpace = _size.Area() - (formatLabel.size() + _text.size());

	size_t i = 0;
	for (; i < pixelVec.size() && i < formatLabel.size(); i++) {
		pixelVec[i].character = formatLabel[i];
		pixelVec[i].color = _color;
	}

	auto textIter = _text.begin();
	for (; i < pixelVec.size() - availableEmptySpace && textIter != _text.end(); i++, textIter++) {
		pixelVec[i].character = *textIter;
		pixelVec[i].color = _color;
	}

	for (; i < pixelVec.size(); i++) {
		pixelVec[i].character = ' ';
		pixelVec[i].color = _color;
	}
}

} // namespace tefk