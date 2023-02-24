#include "label.hpp"

namespace tefk {

Label::Label()
    : GUIComponent{}
{}

void Label::SetText(TefkString text) {
    _text = text;
}

TefkString Label::GetContent() {
    return _text;
}

void Label::GetPixelVector(PixelVector& pixelVec) {
    size_t availableEmptySpace = _size.Area() - _text.size();
    TefkString canvasString = _text + TefkString(availableEmptySpace, ' ');

    for (size_t i = 0; i < pixelVec.size(); i++) {
        pixelVec[i].character = canvasString[i];
        pixelVec[i].color = _color;
    }
}

} // namespace tefk
