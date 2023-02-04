#include "text.hpp"

namespace tefk {

// Cursor

Text::Cursor::Cursor(list_type& text) 
	: _list{ &text },
	  _iter{ text.begin() },
	  _index{ 0 }
{}

bool Text::Cursor::AtListBegin() {
	return _iter == _list->begin();
}

bool Text::Cursor::AtListEnd() {
	return _iter == _list->end();
}

void Text::Cursor::Next() {
	if (AtListEnd())
		return;

	_iter++;
	_index++;
}

void Text::Cursor::Prev() {
	if (AtListBegin())
		return;

	_iter--;
	_index--;
}

void Text::Cursor::Move(size_type offset) {
	std::advance(_iter, offset);
	_index += offset;
}

void Text::Cursor::MoveToIndex(size_type index) {
	// Cast to a signed type to allow negative offset
	std::advance(_iter, static_cast<long long>(index - _index));
	_index = index;
}

Text::list_type::iterator Text::Cursor::Iter() {
	return _iter;
}

Text::char_type Text::Cursor::Char() {
	return *_iter;
}

Text::size_type Text::Cursor::Index() {
	return _index;
}

void Text::Cursor::SetText(list_type& text) {
	_list = &text;
	_iter = text.begin();
	_index = 0;
}

// TODO - Remove this method after optimization
void Text::Cursor::Iter(list_type::iterator iter) {
	_iter = iter;
}

char Text::Cursor::Delete() {
	if (AtListBegin())
		return '\0';

	char deletedChar = *--_iter;
	_iter = _list->erase(_iter);
	_index--;
	return deletedChar;
}

void Text::Cursor::Add(char_type ch) {
	_list->insert(_iter, ch);
	_index++;
}

// Text base component

Text::Text()
	: GUIComponent{},
	  _cursor{ _text }
{}

Text::string_type Text::GetText() {
	std::string text;
	for (auto ch : _text)
		text.push_back(ch);
	return text;
}

void Text::MoveCursorRight() {
	_cursor.Next();
}

void Text::MoveCursorLeft() {
	_cursor.Prev();
}

void Text::MoveCursorUp() {
	// TODO - fix cursor going to beginning of line when at end of line
	if (_text.begin() == _text.end())
		return;

	size_t spacesFromLeft = SpacesFromLeft();
	size_t previousRowSize = 0;

	// Move cursor to start of line
	if (_cursor.AtListEnd() || (!_cursor.AtListBegin() && _cursor.Char() == '\n'))
		MoveCursorLeft();

	while (!_cursor.AtListBegin() && _cursor.Char() != '\n')
		MoveCursorLeft();

	// Move cursor to start of previous line
	if (!_cursor.AtListBegin()) {
		MoveCursorLeft();
		previousRowSize++;
	}

	while (!_cursor.AtListBegin() && _cursor.Char() != '\n') {
		MoveCursorLeft();
		previousRowSize++;
	}

	if (!_cursor.AtListEnd() && !_cursor.AtListBegin() && _cursor.Char() == '\n')
		MoveCursorRight();

	// Move cursor right by offset of previous line
	size_t offset = (std::min)(previousRowSize, spacesFromLeft);
	_cursor.Move(offset);
}

void Text::MoveCursorDown() {
	if (_text.begin() == _text.end())
		return;

	size_t spacesFromLeft = SpacesFromLeft();

	// Move cursor to start of next line
	while (!_cursor.AtListEnd() && _cursor.Char() != '\n')
		MoveCursorRight();

	if (!_cursor.AtListEnd())
		MoveCursorRight();

	// Move cursor right by offset
	while (spacesFromLeft && !_cursor.AtListEnd() && _cursor.Char() != '\n') {
		MoveCursorRight();
		spacesFromLeft--;
	}
}

void Text::MoveCursorNextWord() {
	if (_cursor.AtListEnd())
		return;

	if (_cursor.Char() == '\n')
		MoveCursorRight();

	// Move forwards until space or newline reached
	while (!_cursor.AtListEnd() && _cursor.Char() == ' ' && _cursor.Char() != '\n')
		MoveCursorRight();

	// Move forwards until non-space or newline reached
	while (!_cursor.AtListEnd() && _cursor.Char() != ' ' && _cursor.Char() != '\n')
		MoveCursorRight();
}

void Text::MoveCursorPrevWord() {
	if (_cursor.AtListBegin())
		return;

	if (_cursor.AtListEnd() || _cursor.Char() == '\n')
		MoveCursorLeft();

	// Move backwards until space or newline reached
	while (!_cursor.AtListBegin() && _cursor.Char() == ' ' && _cursor.Char() != '\n')
		MoveCursorLeft();

	// Move backwards until non-space or newline reached
	while (!_cursor.AtListBegin() && _cursor.Char() != ' ' && _cursor.Char() != '\n')
		MoveCursorLeft();
}

void Text::AddChar(char_type ch) {
	_cursor.Add(ch);

	Action action;
	action._actionType = Action::INSERT_TEXT;
	action._text = ch;
	action._index = _cursor.Index();
	AddAction(action);
}

void Text::NewLine() {
	AddChar('\n');
}

void Text::DeleteChar() {
	if (_cursor.AtListBegin())
		return;

	char deletedChar = _cursor.Delete();

	Action action;
	action._actionType = Action::DELETE_TEXT;
	action._text = deletedChar;
	action._index = _cursor.Index();
	AddAction(action);
}

void Text::DeleteWord() {
	if (_cursor.AtListBegin())
		return;

	auto last = _cursor.Iter();

	MoveCursorPrevWord();

	string_type deletedString = SubstringFromList(_cursor.Iter(), last);
	_text.erase(_cursor.Iter(), last);
	_cursor.Iter(last);

	Action action;
	action._actionType = Action::DELETE_TEXT;
	action._text = deletedString;
	action._index = _cursor.Index();
	AddAction(action);
}

void Text::Undo() {
	if (_actions.empty())
		return;

	_cursor.MoveToIndex(_actions.top()._index);

	switch (_actions.top()._actionType) {
	case Action::INSERT_TEXT:
		for (long long i = 0; i < _actions.top()._text.size(); i++)
			_cursor.Delete();
		break;
	case Action::DELETE_TEXT:
		for (auto ch : _actions.top()._text)
			_cursor.Add(ch);
		break;
	}

	_actions.pop();
}

void Text::AddAction(Action action) {
	_actions.push(action);
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
	auto iter = _cursor.Iter();

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

Text::string_type Text::SubstringFromList(std::list<char_type>::iterator begin, std::list<char_type>::iterator end) {
	string_type substring;

	// Build substring from characters between 'begin' (inclusively) and 'end' (exclusively) iterators
	while (begin != _text.end() && begin != end)
		substring += *begin++;

	return substring;
}

} // namespace tefk
