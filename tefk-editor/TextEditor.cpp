#include "TextEditor.h"

namespace tefk {

// Cursor

TextEditor::Cursor::Cursor(std::list<ChType>& text)
    : _list(&text)
    , _iter(text.begin())
    , _index(0)
{}

bool TextEditor::Cursor::AtListBegin()
{
    return _iter == _list->begin();
}

bool TextEditor::Cursor::AtListEnd()
{
    return _iter == _list->end();
}

void TextEditor::Cursor::Next()
{
    if (AtListEnd())
        return;

    _iter++;
    _index++;
}

void TextEditor::Cursor::Prev()
{
    if (AtListBegin())
        return;

    _iter--;
    _index--;
}

void TextEditor::Cursor::Move(size_t offset)
{
    std::advance(_iter, offset);
    _index += offset;
}

void TextEditor::Cursor::MoveToIndex(size_t index)
{
    // Cast to a signed type to allow negative offset
    std::advance(_iter, static_cast<long long>(index - _index));
    _index = index;
}

std::list<ChType>::iterator TextEditor::Cursor::Iter()
{
    return _iter;
}

ChType TextEditor::Cursor::Char()
{
    return *_iter;
}

size_t TextEditor::Cursor::Index()
{
    return _index;
}

void TextEditor::Cursor::SetText(std::list<ChType>& text)
{
    _list = &text;
    _iter = text.begin();
    _index = 0;
}

ChType TextEditor::Cursor::Delete()
{
    if (AtListBegin())
        return '\0';

    ChType deletedChar = *--_iter;
    _iter = _list->erase(_iter);
    _index--;
    return deletedChar;
}

ChType TextEditor::Cursor::DeleteFront()
{
    if (AtListEnd())
        return '\0';

    ChType deletedChar = *_iter;
    _iter = _list->erase(_iter);
    return deletedChar;
}

void TextEditor::Cursor::Add(ChType ch)
{
    _list->insert(_iter, ch);
    _index++;
}

TextEditor::TextEditor()
    : _cursor(_text)
    , _aimedCursorRowIndex(0)
{}
 
void TextEditor::SetText(std::vector<ChType> text)
{
    _text.clear();
    for (auto ch : text)
        _text.push_back(ch);
    _cursor.SetText(_text);
}

std::vector<ChType> TextEditor::GetText()
{
    std::vector<ChType> text;
    for (auto ch : _text)
        text.push_back(ch);
    return text;
}

void TextEditor::MoveCursorRight(bool adjustAimedCursorRowIndex)
{
    _cursor.Next();
    if (adjustAimedCursorRowIndex)
        _aimedCursorRowIndex = RowIndex();
}

void TextEditor::MoveCursorLeft(bool adjustAimedCursorRowIndex)
{
    _cursor.Prev();
    if (adjustAimedCursorRowIndex)
        _aimedCursorRowIndex = RowIndex();
}

void TextEditor::MoveCursorUp()
{
    MoveCursorPrevLine(false);
    MoveCursorToAimedRowIndex();
}

void TextEditor::MoveCursorDown()
{
    MoveCursorNextLine(false);
    MoveCursorToAimedRowIndex();
}

void TextEditor::MoveCursorNextWord()
{
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

void TextEditor::MoveCursorPrevWord()
{
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

void TextEditor::MoveCursorStartLine(bool adjustAimedCursorRowIndex)
{
    if (_cursor.AtListBegin())
        return;

    do MoveCursorLeft(adjustAimedCursorRowIndex);
    while (!_cursor.AtListBegin() && _cursor.Char() != '\n');

    if (_cursor.Char() == '\n')
        MoveCursorRight(adjustAimedCursorRowIndex);
}

void TextEditor::MoveCursorEndLine(bool adjustAimedCursorRowIndex)
{
    while (!_cursor.AtListEnd() && _cursor.Char() != '\n')
        MoveCursorRight(adjustAimedCursorRowIndex);
}

void TextEditor::MoveCursorNextLine(bool adjustAimedCursorRowIndex)
{
    MoveCursorEndLine(adjustAimedCursorRowIndex);
    MoveCursorRight(adjustAimedCursorRowIndex);
}

void TextEditor::MoveCursorPrevLine(bool adjustAimedCursorRowIndex)
{
    MoveCursorStartLine(adjustAimedCursorRowIndex);
    MoveCursorLeft(adjustAimedCursorRowIndex);
}

void TextEditor::MoveCursorToAimedRowIndex()
{
    MoveCursorStartLine(false);
    for (size_t i = 0; i < _aimedCursorRowIndex && !_cursor.AtListEnd() && _cursor.Char() != '\n'; i++)
        MoveCursorRight(false);
}

void TextEditor::AddChar(ChType ch)
{
    _cursor.Add(ch);

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::INSERT_TEXT;
    action._text.resize(1);
    action._text[0] = ch;
    action._index = _cursor.Index();
    AddAction(action);
}

void TextEditor::NewLine()
{
    AddChar('\n');
}

void TextEditor::DeleteChar()
{
    if (_cursor.AtListBegin())
        return;

    ChType deletedChar = _cursor.Delete();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text.resize(1);
    action._text[0] = deletedChar;
    action._index = _cursor.Index();
    AddAction(action);
}

void TextEditor::DeleteWord()
{
    // TODO - Fix if cursor on char in front of spaces, only one space deleted
    if (_cursor.AtListBegin())
        return;

    auto last = _cursor.Iter();

    MoveCursorPrevWord();

    std::vector<ChType> deletedString = SubstringFromList(_cursor.Iter(), last);
    for (auto _ : deletedString)
        _cursor.DeleteFront();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text = deletedString;
    action._index = _cursor.Index();
    AddAction(action);
}

void TextEditor::DeleteLine()
{
    // TODO - make sure deletes whole line, including previous line newline (\n) char
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

    std::vector<ChType> deletedString = SubstringFromList(_cursor.Iter(), last);
    for (auto _ : deletedString)
        _cursor.DeleteFront();

    _aimedCursorRowIndex = RowIndex();

    Action action;
    action._actionType = Action::DELETE_TEXT;
    action._text = deletedString;
    action._index = _cursor.Index();
    AddAction(action);
}

void TextEditor::Undo()
{
    ExecuteAction(_actions, _undoneActions);
}

void TextEditor::Redo()
{
    ExecuteAction(_undoneActions, _actions);
}

void TextEditor::AddAction(Action action)
{
    _actions.push(action);
    _undoneActions = std::stack<Action>();
}

void TextEditor::ExecuteAction(std::stack<Action>& takeStack, std::stack<Action>& dumpStack)
{
    if (takeStack.empty())
        return;

    // Create new action in opposite stack
    dumpStack.push(takeStack.top());

    Action *currAction = &takeStack.top(),
           *newAction = &dumpStack.top();

    _cursor.MoveToIndex(currAction->_index);

    switch (currAction->_actionType)
    {
    case Action::INSERT_TEXT:
        for (size_t i = 0; i < currAction->_text.size(); i++)
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

size_t TextEditor::RowIndex()
{
    if (_cursor.AtListBegin())
        return 0;

    size_t index = 0;
    auto iter = _cursor.Iter();

    // Moving to newline of previous line or beginning of text
    do
    {
        iter--;
        index++;
    } while (iter != _text.begin() && *iter != '\n');

    // If iterator on newline of previous line, adjust index
    if (*iter == '\n')
        index--;

    return index;
}

std::vector<ChType> TextEditor::SubstringFromList(std::list<ChType>::iterator begin, std::list<ChType>::iterator end)
{
    std::vector<ChType> substring;

    // Build substring from characters between 'begin' (inclusively) and 'end' (exclusively) iterators
    while (begin != _text.end() && begin != end)
        substring.push_back(*begin++);

    return substring;
}

} // namespace tefk
