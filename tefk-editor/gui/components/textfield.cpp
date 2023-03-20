#include "textfield.hpp"

namespace tefk {

TextField::TextField()
    : Text{}
{}

TefkString TextField::GetLabel() {
    return _label;
}

void TextField::SetLabel(TefkString label) {
    _label = label;
}

TefkString TextField::GetFormattedString() {
    return _label + ": " + GetText();
}

void TextField::SetOnSubmit(std::function<void()> func) {
    _onSubmit = func;
}

bool TextField::CatchEventFromBaseComponent(Event event) {
    // TODO - catch event and do something with it
    bool eventCaught = true;

    if (event.type == Event::Type::CHARACTER) {
        switch (event.input) {
        case VK_RETURN:
            _onSubmit();
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

TefkCoordSizeT TextField::GetContentWidth() {
    return (std::min)(GetFormattedString().size(), _size.X);
}

TefkCoordSizeT TextField::GetContentHeight() {
    return (TefkCoordSizeT)std::ceil(GetFormattedString().size() / (double)_size.X);
}

void TextField::GetPixelVector(PixelVector& pixelVec) {
    TefkString formatLabel = _label + ": ";

    size_t i = 0;
    for (; i < pixelVec.size() && i < formatLabel.size(); i++) {
        pixelVec[i].character = formatLabel[i];
        pixelVec[i].color = _color;
    }

    auto textIter = _text.begin();
    for (; i < pixelVec.size() && textIter != _text.end(); i++, textIter++) {
        pixelVec[i].character = *textIter;
        pixelVec[i].color = _color;
    }
}

} // namespace tefk
