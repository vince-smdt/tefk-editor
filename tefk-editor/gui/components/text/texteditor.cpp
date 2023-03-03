#include "texteditor.hpp"

namespace tefk {

TextEditor::TextEditor()
    : Text{}
{
    _sizeBehaviour = SizeBehaviour::FILL;
}

void TextEditor::SetText(TefkString text) {
    _text.clear();
    for (auto ch : text)
        _text.push_back(ch);
    _cursor.SetText(_text);
}

void TextEditor::Tab() {
    for (size_t i = 0; i < 4; i++)
        AddChar(' ');
}

TefkString TextEditor::GetContent() {
    return GetText();
}

bool TextEditor::CatchEventFromBaseComponent(Event event) {
    bool eventCaught = true;

    if (event.type == Event::Type::CHARACTER) {
        switch (event.input) {
        case VK_RETURN:
            NewLine();
            break;
        case VK_TAB:
            Tab();
            break;
        default:
            eventCaught = false;
        }
    }
    else {
        eventCaught = false;
    }

    return eventCaught;
}

void TextEditor::GetPixelVector(PixelVector& pixelVec) {
    size_t i = 0;
    auto textIter = _text.begin();

    for (; i < pixelVec.size(); i++, textIter++) {
        // Invert color if cursor at current character
        if (textIter == _cursor.Iter())
            pixelVec[i].color = _color.Inverse();

        // If all text printed, break out of loop
        if (textIter == _text.end())
            break;

        if (*textIter != '\n') {
            // Set character
            pixelVec[i].character = *textIter;
        }
        else {
            // Set i to beginning of next pixel row
            i = ((i + _size.X) / _size.X) * _size.X - 1;
        }
    }
}

} // namespace tefk
