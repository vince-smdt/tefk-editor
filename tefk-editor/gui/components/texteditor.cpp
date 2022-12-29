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

	// If input text can't fit in parent component, shorten string
	std::string truncatedText = (_text.size() > _size.X * _size.Y)
		? _text.substr(_text.size() - (_size.X * _size.Y))
		: _text;

	// Print label
	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(RowSize() * currRow) < truncatedText.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = truncatedText.substr((int)(currRow * RowSize()), RowSize());
		std::cout.write(row.c_str(), row.size());
	}
}

}