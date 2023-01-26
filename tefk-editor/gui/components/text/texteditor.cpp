#include "texteditor.hpp"

namespace tefk {

TextEditor::TextEditor()
	: Text{}
{}

// TODO - load text correctly, currently unable to load text from file
void TextEditor::SetText(std::string text) {
	_text.clear();
	for (auto ch : text)
		_text.push_back(ch);
	_cursor = _text.begin();
}

std::string TextEditor::GetContent() {
	std::string text;
	for (auto ch : _text)
		text.push_back(ch);
	return text;
}

void TextEditor::DrawOnCanvas() {
	if (_size.X * _size.Y <= 0)
		return;

	auto iter = _text.begin();
	bool fillRowWithSpaces = false;
	bool cursorPrinted = false;

	for (size_t pxInd = 0; pxInd < _size.Area(); pxInd++) {
		// Set pixel position on canvas and pointer to current pixel
		Coord pxPos = { pxInd % _size.X, pxInd / _size.X };
		Pixel* pixel = &GetCanvas().PixelAt(pxPos.X + _pos.X, pxPos.Y + _pos.Y);

		// Reset flag if new row
		if (pxPos.X == 0)
			fillRowWithSpaces = false;

		// Color pixel
		if (_cursor == iter && !cursorPrinted && !fillRowWithSpaces) {
			pixel->color = _color.Inverse();
			cursorPrinted = true;
		}
		else {
			pixel->color = _color;
		}

		// Assign pixel character and move iterator
		if (fillRowWithSpaces || iter == _text.end()) {
			pixel->character = ' ';
		}
		else {
			if (*iter == '\n') {
				fillRowWithSpaces = true;
				pixel->character = ' ';
			}
			else {
				pixel->character = *iter;
			}
			iter++;
		}
	}
}

} // namespace tefk