#include "text.hpp"

namespace tefk {

Text::Text()
	: GUIComponent{}
{
	_cursor = _text.begin();
}

Text::value_type Text::GetText() {
	std::string text;
	for (auto ch : _text)
		text.push_back(ch);
	return text;
}

void Text::MoveCursorRight() {
	if (_cursor != _text.end()) {
		_cursor++;
		_currAction._movementOffset--;
	}
}

void Text::MoveCursorLeft() {
	if (_cursor != _text.begin()) {
		_cursor--;
		_currAction._movementOffset++;
	}
}

void Text::MoveCursorUp() {
	// TODO - fix cursor going to beginning of line when at end of line
	if (_text.begin() == _text.end())
		return;

	size_t spacesFromLeft = SpacesFromLeft();
	size_t previousRowSize = 0;

	// Move cursor to start of line
	if (_cursor == _text.end() || (_cursor != _text.begin() && *_cursor == '\n'))
		MoveCursorLeft();

	while (_cursor != _text.begin() && *_cursor != '\n')
		MoveCursorLeft();

	// Move cursor to start of previous line
	if (_cursor != _text.begin()) {
		MoveCursorLeft();
		previousRowSize++;
	}

	while (_cursor != _text.begin() && *_cursor != '\n') {
		MoveCursorLeft();
		previousRowSize++;
	}

	if (_cursor != _text.end() && _cursor != _text.begin() && *_cursor == '\n')
		MoveCursorRight();

	// Move cursor right by offset of previous line
	size_t offset = (std::min)(previousRowSize, spacesFromLeft);
	std::advance(_cursor, offset);
	_currAction._movementOffset -= offset;
}

void Text::MoveCursorDown() {
	if (_text.begin() == _text.end())
		return;

	size_t spacesFromLeft = SpacesFromLeft();

	// Move cursor to start of next line
	while (_cursor != _text.end() && *_cursor != '\n')
		MoveCursorRight();

	if (_cursor != _text.end())
		MoveCursorRight();

	// Move cursor right by offset
	while (spacesFromLeft && _cursor != _text.end() && *_cursor != '\n') {
		MoveCursorRight();
		spacesFromLeft--;
	}
}

void Text::MoveCursorNextWord() {
	if (_cursor == _text.end())
		return;

	if (*_cursor == '\n')
		MoveCursorRight();

	// Move forwards until space or newline reached
	while (_cursor != _text.end() && *_cursor == ' ' && *_cursor != '\n')
		MoveCursorRight();

	// Move forwards until non-space or newline reached
	while (_cursor != _text.end() && *_cursor != ' ' && *_cursor != '\n')
		MoveCursorRight();
}

void Text::MoveCursorPrevWord() {
	if (_cursor == _text.begin())
		return;

	if (_cursor == _text.end() || *_cursor == '\n')
		MoveCursorLeft();

	// Move backwards until space or newline reached
	while (_cursor != _text.begin() && *_cursor == ' ' && *_cursor != '\n')
		MoveCursorLeft();

	// Move backwards until non-space or newline reached
	while (_cursor != _text.begin() && *_cursor != ' ' && *_cursor != '\n')
		MoveCursorLeft();
}

void Text::AddChar(char_type ch) {
	_text.insert(_cursor, ch);

	_currAction._actionType = Action::INSERT_TEXT;
	_currAction._text = ch;
	AddEvent();
}

void Text::NewLine() {
	AddChar('\n');
}

void Text::DeleteChar() {
	if (_cursor == _text.begin())
		return;

	auto last = _cursor;

	MoveCursorLeft();

	value_type deletedString = SubstringFromList(_cursor, last);
	if (!deletedString.empty()) {
		_currAction._actionType = Action::DELETE_TEXT;
		_currAction._text = deletedString;
		_currAction._movementOffset -= deletedString.size();
		AddEvent();
	}

	_cursor = _text.erase(_cursor);
}

void Text::DeleteWord() {
	if (_cursor == _text.begin())
		return;

	auto last = _cursor;

	MoveCursorPrevWord();

	value_type deletedString = SubstringFromList(_cursor, last);
	if (!deletedString.empty()) {
		_currAction._actionType = Action::DELETE_TEXT;
		_currAction._text = deletedString;
		_currAction._movementOffset -= deletedString.size();
		AddEvent();
	}

	_cursor = _text.erase(_cursor, last);
}

void Text::Undo() {
	if (_actions.empty())
		return;

	long long offset = _currAction._movementOffset;

	std::advance(_cursor, offset);

	// TODO - write better code
	_currAction.Reset();
	_currAction._movementOffset = _actions.top()._movementOffset;

	switch (_actions.top()._actionType) {
	case Action::INSERT_TEXT:
		for (long long i = 0; i < _actions.top()._text.size(); i++)
			_cursor = _text.erase(--_cursor); // TODO - reuse already written functions without recording action
		break;
	case Action::DELETE_TEXT:
		for (auto ch : _actions.top()._text)
			_text.insert(_cursor, ch); // TODO - reuse already written functions without recording action
		break;
	}

	_actions.pop();
}

void Text::AddEvent() {
	_actions.push(_currAction);
	_currAction.Reset();
}

void Text::CatchEvent(Event event) {
	// Cancel if component isn't focused
	if (!Focused())
		return;

	if (event.type == Event::Type::CHARACTER) {
		switch (event.input) {
		case VK_BACK:
			DeleteChar();
			break;
		case VK_CTRL_BACKSPACE:
			DeleteWord();
			break;
		case VK_CTRL_Z:
			Undo();
			break;
		default:
			if (!CatchEventFromBaseComponent(event) && event.input > 26)
				AddChar(event.input);
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
		default:
			CatchEventFromBaseComponent(event);
		}
	}
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

Text::value_type Text::SubstringFromList(std::list<char_type>::iterator begin, std::list<char_type>::iterator end) {
	Text::value_type substring;

	// Build substring from characters between 'begin' (inclusively) and 'end' (exclusively) iterators
	while (begin != _text.end() && begin != end)
		substring += *begin++;

	return substring;
}

} // namespace tefk
