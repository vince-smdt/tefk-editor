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

void TextEditor::DrawPixel(Coord pos, Pixel& pixel) {
	bool drawEmptySpace = pos.Y >= _rows.size() || pos.X >= _rows[pos.Y].size();

	pixel.character = drawEmptySpace ? ' ' : _rows[pos.Y][pos.X];
	pixel.color = (GetCursorPos() == pos) ? _color.Inverse() : _color;
}

} // namespace tefk