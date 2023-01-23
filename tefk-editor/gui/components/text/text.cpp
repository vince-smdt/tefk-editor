#include "text.hpp"

namespace tefk {

Text::Text()
	: GUIComponent{ SizeBehaviour::FILL }
{}

Coord Text::GetCursorPos() {
	return Coord(
		_pos.X + short(_cursor.col - _cursor.row->begin()),
		_pos.Y + short(_cursor.row - _rows.begin() - 1)
	);
}

void Text::AddChar(unsigned char ch) {
	_cursor.col = _cursor.row->insert(_cursor.col, ch) + 1;
}

void Text::NewLine() {
	// Create new row and move content after cursor to new row
	size_t colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row = _rows.insert(_cursor.row + 1, "");
	*_cursor.row = (_cursor.row - 1)->substr(colIndex, (_cursor.row - 1)->size() - colIndex);
	(_cursor.row - 1)->erase(colIndex, (_cursor.row - 1)->size() - colIndex);
	_cursor.col = _cursor.row->begin();
}

void Text::DeleteChar() {
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

void Text::DeleteWord() {
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

void Text::MoveCursorRight() {
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

void Text::MoveCursorLeft() {
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

void Text::MoveCursorUp() {
	// If at first row
	if (_cursor.row == _rows.begin()) {
		// Move cursor to beginning of line
		_cursor.col = _cursor.row->begin();
		return;
	}

	// Move cursor to previous row
	size_t colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row--;

	// If cursor column index is bigger than new row, move to end of new row
	// Else, move to same column index of new row
	if (colIndex >= _cursor.row->size()) {
		_cursor.col = _cursor.row->end();
		return;
	}
	_cursor.col = _cursor.row->begin() + colIndex;

}

void Text::MoveCursorDown() {
	// If at last row
	if (_cursor.row == _rows.end() - 1) {
		// Move cursor to end of line
		_cursor.col = _cursor.row->end();
		return;
	}

	// Move cursor to next row
	size_t colIndex = _cursor.col - _cursor.row->begin();
	_cursor.row++;

	// If cursor column index is bigger than new row, move to end of new row
	// Else, move to same column index of new row
	if (colIndex >= _cursor.row->size()) {
		_cursor.col = _cursor.row->end();
		return;
	}
	_cursor.col = _cursor.row->begin() + colIndex;
}

void Text::MoveCursorNextWord() {
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

	while (_cursor.col != _cursor.row->end() && *_cursor.col != ' ')
		_cursor.col++;

	while (_cursor.col != _cursor.row->end() && *_cursor.col == ' ')
		_cursor.col++;
}

void Text::MoveCursorPrevWord() {
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

} // namespace tefk