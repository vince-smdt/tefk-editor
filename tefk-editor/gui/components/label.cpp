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
    for (size_t i = 0; i < pixelVec.size() && i < _text.size(); i++) {
        pixelVec[i].character = _text[i];
        pixelVec[i].color = _color;
    }
}

} // namespace tefk
