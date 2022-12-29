#include "texteditor.hpp"

namespace tefk {

TextEditor::TextEditor()
	: GUIComponent{}
{}

TextEditor::TextEditor(Coord pos, Coord size, TextColor color)
	: GUIComponent{ pos, size, color }
{}

void TextEditor::SetText(std::string text) {
	_text = text;
}

void TextEditor::PrintContent() {
	// TODO - This is the same as the PrintContent method of textfield component,
	//		  either make parent "Text" class for both or modify this method

	// Print label
	size_t offsetIndex = 0,
	       nextBreakingIndex = 0;

	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);

		// Find next breaking char
		for (size_t currRowIndex = 0; currRowIndex + offsetIndex <= _text.size() && currRowIndex < _size.X; currRowIndex++) {
			nextBreakingIndex = currRowIndex + offsetIndex;
			if (currRowIndex + offsetIndex == _text.size() || _text[currRowIndex + offsetIndex] == '\n')
				break;
		}

		// Print entire row
		// TODO - reduce number of std::strings being constructed each loop iteration
		std::string rowText = _text.substr(offsetIndex, nextBreakingIndex - offsetIndex);
		std::string row = rowText + std::string(_size.X - rowText.size(), ' ');
		std::cout.write(row.c_str(), row.size());

		// Set text offset for next iteration
		if (_text[nextBreakingIndex] == '\n')
			nextBreakingIndex++;
		offsetIndex = nextBreakingIndex;
	}
}

}