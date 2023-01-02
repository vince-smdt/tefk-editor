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

	// If text empty, push at least one row into _rows to position cursor
	if (_rows.empty())
		_rows.push_back("");

	// TODO - position cursor elsewhere
	_cursorRow = _rows.begin();
	_cursorCol = _cursorRow->begin();
}

void TextEditor::PrintContent() {
	// Print text
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

	PrintCursor();
}

void TextEditor::PrintCursor() {
	// TEMP - positioning cursor at end of text
	_cursorRow = _rows.end() - 1;
	_cursorCol = _cursorRow->end();

	Coord cursorPos = {
		_pos.X + _cursorCol - _cursorRow->begin(),
		_pos.Y + _cursorRow - _rows.begin()
	};

	// Cancel if cursor out of print area
	// TODO - hide cursor if not in texteditor, not just out of console window
	if (cursorPos.X >= ConsoleAPI::ColCount() || cursorPos.X < 0 || cursorPos.Y >= ConsoleAPI::RowCount() || cursorPos.Y < 0)
		return;

	ConsoleAPI::SetTextColor(_color.Inverse());
	ConsoleAPI::SetCursorPos(cursorPos.Y, cursorPos.X);
	if (_cursorCol != _cursorRow->end())
		std::cout.write(std::string(1, *_cursorCol).c_str(), 1);
	else
		std::cout.write(" ", 1);
}

}