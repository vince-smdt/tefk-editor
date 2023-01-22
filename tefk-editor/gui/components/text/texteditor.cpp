#include "texteditor.hpp"

namespace tefk {

TextEditor::TextEditor()
	: Text{}
{
	_rows.push_back("");
	_cursor.row = _rows.begin();
	_cursor.col = _cursor.row->end();
}

// TODO - load text correctly, currently unable to load text from file
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

std::string TextEditor::GetContent() {
	std::string text;
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

void TextEditor::DrawPixel(short x, short y) {
	Coord cursorPos = {
		_pos.X + short(_cursor.col - _cursor.row->begin()),
		_pos.Y + short(_cursor.row - _rows.begin())
	}; // TODO - optimize so we don't initialize this every pixel

	// Draw editor
	bool drawEmptySpace = y >= _rows.size() || x >= _rows[y].size();

	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).character = drawEmptySpace ? ' ' : _rows[y][x];
	GetCanvas().PixelAt(x + _pos.X, y + _pos.Y).color = _color;

	// Draw cursor
	if (cursorPos.X == x && cursorPos.Y == y)
		GetCanvas().PixelAt(cursorPos.X, cursorPos.Y).color = _color.Inverse();
}

} // namespace tefk