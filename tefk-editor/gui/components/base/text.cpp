#include "text.hpp"

namespace tefk {

// Cursor

Text::Cursor::Cursor(TefkCharList& text) 
    : _list{ &text }
    , _iter{ text.begin() }
    , _index{ 0 }
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

void Text::Cursor::Move(TefkSizeT offset) {
    std::advance(_iter, offset);
    _index += offset;
}

void Text::Cursor::MoveToIndex(TefkSizeT index) {
    // Cast to a signed type to allow negative offset
    std::advance(_iter, static_cast<long long>(index - _index));
    _index = index;
}

Text::TefkCharList::iterator Text::Cursor::Iter() {
    return _iter;
}

TefkChar Text::Cursor::Char() {
    return *_iter;
}

TefkSizeT Text::Cursor::Index() {
    return _index;
}

void Text::Cursor::SetText(TefkCharList& text) {
    _list = &text;
    _iter = text.begin();
    _index = 0;
}

TefkChar Text::Cursor::Delete() {
    if (AtListBegin())
        return '\0';

    TefkChar deletedChar = *--_iter;
    _iter = _list->erase(_iter);
    _index--;
    return deletedChar;
}

TefkChar Text::Cursor::DeleteFront() {
    if (AtListEnd())
        return '\0';

    TefkChar deletedChar = *_iter;
    _iter = _list->erase(_iter);
    return deletedChar;
}

void Text::Cursor::Add(TefkChar ch) {
    _list->insert(_iter, ch);
    _index++;
}

// Text base component

Text::Text()
    : GUIComponent{}
    , _cursor{ _text }
    , _aimedCursorRowIndex{ 0 }
{}

TefkString Text::GetText() {
    TefkString text;
    for (auto ch : _text)
        text.push_back(ch);
    return text;
}

void Text::MoveCursorRight(bool adjustAimedCursorRowIndex) {
    _cursor.Next();
    if (adjustAimedCursorRowIndex)
        _aimedCursorRowIndex = RowIndex();
}

void Text::MoveCursorLeft(bool adjustAimedCursorRowIndex) {
    _cursor.Prev();
    if (adjustAimedCursorRowIndex)
        _aimedCursorRowIndex = RowIndex();
}

void Text::MoveCursorUp() {
    MoveCursorPrevLine(false);
    MoveCursorToAimedRowIndex();
}

void Text::MoveCursorDown() {
    MoveCursorNextLine(false);
    MoveCursorToAimedRowIndex();
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

    if (_cursor.AtListEnd() || _cursor.Char() == '\n' || _cursor.Char() != ' ')
        MoveCursorLeft();

    // Move backwards until space or newline reached
    while (!_cursor.AtListBegin() && _cursor.Char() == ' ' && _cursor.Char() != '\n')
        MoveCursorLeft();

    // Move backwards until non-space or newline reached
    while (!_cursor.AtListBegin() && _cursor.Char() != ' ' && _cursor.Char() != '\n')
        MoveCursorLeft();
}

void Text::MoveCursorStartLine(bool adjustAimedCursorRowIndex) {
    if (_cursor.AtListBegin())
        return;

    do MoveCursorLeft(adjustAimedCursorRowIndex);
    while (!_cursor.AtListBegin() && _cursor.Char() != '\n');

    if (_cursor.Char() == '\n')
        MoveCursorRight(adjustAimedCursorRowIndex);
}

void Text::MoveCursorEndLine(bool adjustAimedCursorRowIndex) {
    while (!_cursor.AtListEnd() && _cursor.Char() != '\n')
        MoveCursorRight(adjustAimedCursorRowIndex);
}

void Text::MoveCursorNextLine(bool adjustAimedCursorRowIndex) {
    MoveCursorEndLine(adjustAimedCursorRowIndex);
    MoveCursorRight(adjustAimedCursorRowIndex);
}

void Text::MoveCursorPrevLine(bool adjustAimedCursorRowIndex) {
    MoveCursorStartLine(adjustAimedCursorRowIndex);
    MoveCursorLeft(adjustAimedCursorRowIndex);
}

void Text::MoveCursorToAimedRowIndex() {
    MoveCursorStartLine(false);
    for (TefkSizeT i = 0; i < _aimedCursorRowIndex && !_cursor.AtListEnd() && _cursor.Char() != '\n'; i++)
        MoveCursorRight(false);
}

void Text::AddChar(TefkChar ch) {
    _cursor.Add(ch);

    _aimedCursorRowIndex = RowIndex();

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

    TefkChar deletedChar = _cursor.Delete();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text = deletedChar;
    action._index = _cursor.Index();
    AddAction(action);
}

void Text::DeleteWord() {
    // TODO - Fix if cursor on char in front of spaces, only one space deleted
    if (_cursor.AtListBegin())
        return;

    auto last = _cursor.Iter();

    MoveCursorPrevWord();

    TefkString deletedString = SubstringFromList(_cursor.Iter(), last);
    for (auto _ : deletedString)
        _cursor.DeleteFront();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text = deletedString;
    action._index = _cursor.Index();
    AddAction(action);
}

void Text::DeleteLine() {
    if (_text.empty())
        return;

    while (!_cursor.AtListEnd() && _cursor.Char() != '\n')
        MoveCursorRight();

    auto last = _cursor.Iter();
    if (last != _text.end())
        last++;

    if (_cursor.AtListEnd() || _cursor.Char() == '\n')
        MoveCursorLeft();

    while (!_cursor.AtListBegin() && _cursor.Char() != '\n')
        MoveCursorLeft();

    if (!_cursor.AtListBegin() && _cursor.Char() == '\n')
        MoveCursorRight();

    TefkString deletedString = SubstringFromList(_cursor.Iter(), last);
    for (auto _ : deletedString)
        _cursor.DeleteFront();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text = deletedString;
    action._index = _cursor.Index();
    AddAction(action);
}

void Text::Undo() {
    ExecuteAction(_actions, _undoneActions);
}

void Text::Redo() {
    ExecuteAction(_undoneActions, _actions);
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
        case KC_CTRL_BACKSPACE:
            DeleteWord();
            break;
        case KC_CTRL_L:
            DeleteLine();
            break;
        case KC_CTRL_Y:
            Redo();
            break;
        case KC_CTRL_Z:
            Undo();
            break;
        default:
            if (!CatchEventFromBaseComponent(event) && event.input > 27)
                AddChar(event.input);
        }
    }
    else if (event.type == Event::Type::SPECIAL_CHARACTER) {
        switch (event.input) {
        case KC_ARROW_RIGHT:
            MoveCursorRight();
            break;
        case KC_ARROW_LEFT:
            MoveCursorLeft();
            break;
        case KC_ARROW_UP:
            MoveCursorUp();
            break;
        case KC_ARROW_DOWN:
            MoveCursorDown();
            break;
        case KC_CTRL_ARROW_RIGHT:
            MoveCursorNextWord();
            break;
        case KC_CTRL_ARROW_LEFT:
            MoveCursorPrevWord();
            break;
        default:
            CatchEventFromBaseComponent(event);
        }
    }
}

void Text::AddAction(Action action) {
    _actions.push(action);
    _undoneActions = std::stack<Action>();
}

void Text::ExecuteAction(std::stack<Action>& takeStack, std::stack<Action>& dumpStack) {
    if (takeStack.empty())
        return;

    // Create new action in opposite stack
    dumpStack.push(takeStack.top());

    Action *currAction = &takeStack.top(),
           *newAction = &dumpStack.top();

    _cursor.MoveToIndex(currAction->_index);

    switch (currAction->_actionType) {
    case Action::INSERT_TEXT:
        for (TefkSizeT i = 0; i < currAction->_text.size(); i++)
            _cursor.Delete();

        newAction->_actionType = Action::DELETE_TEXT;
        newAction->_index -= currAction->_text.size();

        break;
    case Action::DELETE_TEXT:
        for (auto ch : currAction->_text)
            _cursor.Add(ch);

        newAction->_actionType = Action::INSERT_TEXT;
        newAction->_index += currAction->_text.size();

        break;
    }

    takeStack.pop();

    _aimedCursorRowIndex = RowIndex();
}

TefkSizeT Text::RowIndex() {
    if (_cursor.AtListBegin())
        return 0;

    TefkSizeT index = 0;
    auto iter = _cursor.Iter();

    // Moving to newline of previous line or beginning of text
    do {
        iter--;
        index++;
    } while (iter != _text.begin() && *iter != '\n');

    // If iterator on newline of previous line, adjust index
    if (*iter == '\n')
        index--;

    return index;
}

TefkString Text::SubstringFromList(std::list<TefkChar>::iterator begin, std::list<TefkChar>::iterator end) {
    TefkString substring;

    // Build substring from characters between 'begin' (inclusively) and 'end' (exclusively) iterators
    while (begin != _text.end() && begin != end)
        substring += *begin++;

    return substring;
}

} // namespace tefk
