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

	_cursor.row = _rows.begin();
	_cursor.col = _cursor.row->begin();
}

std::string TextEditor::GetText() {
	std::string text = "";
	for (std::string row : _rows)
		text.append(row + '\n');
	return text.substr(0, text.size() - 1);
}

void TextEditor::CatchEvent(Event& event) {
	if (event.type == Event::Type::CHARACTER) {
		switch (event.input) {
		case VK_BACK:
			DeleteChar();
			break;
		case VK_CTRL_BACKSPACE:
			DeleteWord();
			break;
		case VK_RETURN:
			NewLine();
			break;
		default:
			if (event.input > 26)
				AddChar(event.input);
			break;
		}
	}
	else if (event.type == Event::Type::SPECIAL_CHARACTER) {
		switch (event.input) {
		case VK_ARROW_RIGHT:
			MoveCursorRight();
			break;
		case VK_ARROW_LEFT:
			MoveCursorLeft();
			break;
		case VK_ARROW_UP:
			MoveCursorUp();
			break;
		case VK_ARROW_DOWN:
			MoveCursorDown();
			break;
		case VK_CTRL_ARROW_RIGHT:
			MoveCursorNextWord();
			break;
		case VK_CTRL_ARROW_LEFT:
			MoveCursorPrevWord();
			break;
		}
	}
}

void TextEditor::AddChar(unsigned char ch) {
	_cursor.col = _cursor.row->insert(_cursor.col, ch) + 1;
}

void TextEditor::NewLine() {
	// Create new row and move content after cursor to new row
	size_t colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row = _rows.insert(_cursor.row + 1, "");
	*_cursor.row = (_cursor.row - 1)->substr(colIndex, (_cursor.row - 1)->size() - colIndex);
	(_cursor.row - 1)->erase(colIndex, (_cursor.row - 1)->size() - colIndex);
	_cursor.col = _cursor.row->begin();
}

void TextEditor::DeleteChar() {
	// If at beginning of row
	if (_cursor.col == _cursor.row->begin()) {
		// If at begining of file, cancel
		if (_cursor.row == _rows.begin())
			return;

		// Move content of current row to previous row, then delete current row
		size_t currRowSize = (_cursor.row - 1)->size();
		(_cursor.row - 1)->append(*_cursor.row);
		_cursor.row = _rows.erase(_cursor.row);
		_cursor.col = (--_cursor.row)->begin() + currRowSize;
		return;
	}
	_cursor.row->erase(--_cursor.col);
}

void TextEditor::DeleteWord() {
	// If cursor at beginning or row
	if (_cursor.col == _cursor.row->begin()) {
		// If cursor on first row, cancel
		if (_cursor.row == _rows.begin())
			return;

		// Delete word on previous row
		DeleteChar();
		DeleteWord();
		return;
	}

	size_t colIndex = _cursor.col - _cursor.row->begin();
	bool selectedChar = false; // if at least one non-space char selected

	_cursor.col--;

	// Position cursor on last char if pointing to end() iterator
	if (_cursor.col == _cursor.row->end())
		_cursor.col--;

	// Skip spaces
	while (*_cursor.col == ' ' && _cursor.col != _cursor.row->begin())
		_cursor.col--;

	// Skip letters of word to delete
	while (*_cursor.col != ' ' && _cursor.col != _cursor.row->begin()) {
		selectedChar = true;
		_cursor.col--;
	}

	// Leave space in front of previous word
	if (selectedChar && *_cursor.col == ' ')
		_cursor.col++;

	size_t selectionSize = colIndex - (_cursor.col - _cursor.row->begin());
	size_t newColIndex = _cursor.col - _cursor.row->begin();

	// Delete word
	_cursor.row->erase(newColIndex, selectionSize);
	_cursor.col = _cursor.row->begin() + newColIndex;
}

void TextEditor::MoveCursorRight() {
	// If at end of row
	if (_cursor.col == _cursor.row->end()) {
		// Cancel if cursor already at eof
		if (_cursor.row == _rows.end() - 1)
			return;

		// Move cursor to next row
		_cursor.col = (++_cursor.row)->begin();
		return;
	}

	// Move cursor to next char
	_cursor.col++;
}

void TextEditor::MoveCursorLeft() {
	// If at beginning of row
	if (_cursor.col == _cursor.row->begin()) {
		// Cancel if cursor already at bof
		if (_cursor.row == _rows.begin())
			return;

		// Move cursor to previous row
		_cursor.col = (--_cursor.row)->end();
		return;
	}

	// Move cursor to previous char
	_cursor.col--;
}

void TextEditor::MoveCursorUp() {
	// If at first row
	if (_cursor.row == _rows.begin()) {
		// Move cursor to beginning of line
		_cursor.col = _cursor.row->begin();
		return;
	}

	// Move cursor to previous row
	int colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row--;
	
	// If cursor column index is bigger than new row, move to end of new row
	// Else, move to same column index of new row
	if (colIndex >= _cursor.row->size()) {
		_cursor.col = _cursor.row->end();
		return;
	}
	_cursor.col = _cursor.row->begin() + colIndex;

}

void TextEditor::MoveCursorDown() {
	// If at last row
	if (_cursor.row == _rows.end() - 1) {
		// Move cursor to end of line
		_cursor.col = _cursor.row->end();
		return;
	}

	// Move cursor to next row
	int colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row++;

	// If cursor column index is bigger than new row, move to end of new row
	// Else, move to same column index of new row
	if (colIndex >= _cursor.row->size()) {
		_cursor.col = _cursor.row->end();
		return;
	}
	_cursor.col = _cursor.row->begin() + colIndex;
}

void TextEditor::MoveCursorNextWord() {
	// If at end of row
	if (_cursor.col == _cursor.row->end()) {
		// Cancel if at end of file
		if (_cursor.row == _rows.end() - 1)
			return;

		// Go to next row
		_cursor.col = (++_cursor.row)->begin();
		return;
	}

	// Go to next word
	_cursor.col++;

	while (_cursor.col != _cursor.row->end()  && *_cursor.col != ' ')
		_cursor.col++;

	while (_cursor.col != _cursor.row->end() && *_cursor.col == ' ')
		_cursor.col++;
}

void TextEditor::MoveCursorPrevWord() {
	// If at beginning of row
	if (_cursor.col == _cursor.row->begin()) {
		// Cancel if at beginning of file
		if (_cursor.row == _rows.begin())
			return;

		// Go to prev row
		_cursor.col = (--_cursor.row)->end();
		return;
	}

	// Go to prev word
	_cursor.col--;

	while (_cursor.col != _cursor.row->begin() && *_cursor.col != ' ')
		_cursor.col--;

	while (_cursor.col != _cursor.row->begin() && *_cursor.col == ' ')
		_cursor.col--;
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
	Coord cursorPos = {
		_pos.X + _cursor.col - _cursor.row->begin(),
		_pos.Y + _cursor.row - _rows.begin()
	};

	// Cancel if cursor out of print area
	// TODO - hide cursor if not in texteditor, not just out of console window
	if (cursorPos.X >= ConsoleAPI::ColCount() || cursorPos.X < 0 || cursorPos.Y >= ConsoleAPI::RowCount() || cursorPos.Y < 0)
		return;

	ConsoleAPI::SetTextColor(_color.Inverse());
	ConsoleAPI::SetCursorPos(cursorPos.Y, cursorPos.X);
	if (_cursor.col != _cursor.row->end())
		std::cout.write(std::string(1, *_cursor.col).c_str(), 1);
	else
		std::cout.write(" ", 1);
}

}