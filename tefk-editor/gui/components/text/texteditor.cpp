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

    for (; i < pixelVec.size(); i++) {
        // Invert color if cursor at current character
        pixelVec[i].color = (textIter == _cursor.Iter()) ? _color.Inverse() : _color;

        if (textIter != _text.end() && *textIter != '\n') {
            // Set character
            pixelVec[i].character = *textIter;
        }
        else {
            // If newline, set rest of row as white space
            pixelVec[i].character = ' ';
            i++;
            for (; i % _size.X != 0; i++) {
                pixelVec[i].character = ' ';
                pixelVec[i].color = _color;
            }
            i--;
        }
    
        if (textIter == _text.end()) {
            i++;
            break;
        }
        else
            textIter++;
    }

    for (; i < pixelVec.size(); i++) {
        pixelVec[i].character = ' ';
        pixelVec[i].color = _color;
    }
}

} // namespace tefk
