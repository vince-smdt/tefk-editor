#include "texteditor.hpp"

namespace tefk {

TextEditor::TextEditor()
	: GUIComponent{}
{}

TextEditor::TextEditor(Coord pos, Coord size, TextColor color)
	: GUIComponent{ pos, size, color }
{}

void TextEditor::SetText(std::string text) {
	size_t currLineBreak = 0,
	       nextLineBreak = 0;

	_rows.clear();
	while (true) {
		nextLineBreak = text.find_first_of('\n', currLineBreak);
		_rows.push_back(text.substr(currLineBreak, nextLineBreak - currLineBreak));
		if (nextLineBreak == std::string::npos)
			break;
		currLineBreak = ++nextLineBreak;
	};
}

void TextEditor::PrintContent() {
	for (size_t currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);

		std::string rowText = (currRow < _rows.size())
			? _rows[currRow]
			: "";
		
		std::string row = (rowText.size() <= _size.X)
			? rowText + std::string(_size.X - rowText.size(), ' ')
			: rowText.substr(0, _size.X);
		
		std::cout.write(row.c_str(), row.size());
	}
}

}