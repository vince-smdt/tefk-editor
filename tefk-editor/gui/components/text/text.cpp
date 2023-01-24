#include "text.hpp"

namespace tefk {

Text::Text()
	: GUIComponent{ SizeBehaviour::FILL }
{
	_cursor = _text.begin();
}

void Text::AddChar(unsigned char ch) {
	_text.insert(_cursor, ch);
}

void Text::NewLine() {
	AddChar('\n');
}

void Text::DeleteChar() {
	if (_cursor != _text.begin())
		_cursor = _text.erase(--_cursor);
}

void Text::DeleteWord() {
	auto last = _cursor;

	MoveCursorPrevWord();
	_cursor = _text.erase(_cursor, last);
}

void Text::MoveCursorRight() {
	if (_cursor != _text.end())
		_cursor++;
}

void Text::MoveCursorLeft() {
	if (_cursor != _text.begin())
		_cursor--;
}

void Text::MoveCursorUp() {
	size_t spacesFromLeft = SpacesFromLeft();
	size_t previousRowSize = 0;

	// Move cursor to start of line
	if (_cursor == _text.end() || (_cursor != _text.begin() && *_cursor == '\n'))
		_cursor--;

	while (_cursor != _text.begin() && *_cursor != '\n')
		_cursor--;

	// Move cursor to start of previous line
	if (_cursor != _text.begin()) {
		_cursor--;
		previousRowSize++;
	}

	while (_cursor != _text.begin() && *_cursor != '\n') {
		_cursor--;
		previousRowSize++;
	}

	if (_cursor != _text.end() && _cursor != _text.begin() && *_cursor == '\n')
		_cursor++;

	// Move cursor right by offset of previous line
	std::advance(_cursor, (std::min)(previousRowSize, spacesFromLeft));
}

void Text::MoveCursorDown() {
	size_t spacesFromLeft = SpacesFromLeft();

	// Move cursor to start of next line
	while (_cursor != _text.end() && *_cursor != '\n')
		_cursor++;

	if (_cursor != _text.end())
		_cursor++;

	// Move cursor right by offset
	while (spacesFromLeft && _cursor != _text.end() && *_cursor != '\n') {
		_cursor++;
		spacesFromLeft--;
	}
}

void Text::MoveCursorNextWord() {
	if (_cursor == _text.end())
		return;

	if (*_cursor == '\n')
		_cursor++;

	// Move forwards until space or newline reached
	while (_cursor != _text.end() && *_cursor == ' ' && *_cursor != '\n')
		_cursor++;

	// Move forwards until non-space or newline reached
	while (_cursor != _text.end() && *_cursor != ' ' && *_cursor != '\n')
		_cursor++;
}

void Text::MoveCursorPrevWord() {
	if (_cursor == _text.begin())
		return;

	if (_cursor == _text.end() || *_cursor == '\n')
		_cursor--;

	// Move backwards until space or newline reached
	while (_cursor != _text.begin() && *_cursor == ' ' && *_cursor != '\n')
		_cursor--;

	// Move backwards until non-space or newline reached
	while (_cursor != _text.begin() && *_cursor != ' ' && *_cursor != '\n')
		_cursor--;
}

size_t Text::SpacesFromLeft() {
	size_t spacesFromLeft = 0;
	auto iter = _cursor;

	if (iter == _text.end() || *iter == '\n') {
		iter--;
		spacesFromLeft++;
	}

	while (iter != _text.begin() && (iter == _text.end() || *iter != '\n')) {
		iter--;
		spacesFromLeft++;
	}

	if (iter != _text.end() && *iter == '\n' && spacesFromLeft > 0)
		spacesFromLeft--;

	return spacesFromLeft;
}

} // namespace tefk
