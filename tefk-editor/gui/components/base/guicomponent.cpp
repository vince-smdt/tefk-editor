#include "guicomponent.hpp"
#include "../../window.hpp"

namespace tefk {

GUIComponent::GUIComponent()
    : _parent{ nullptr }
    , _pos{ 0, 0 }
    , _size{ 0, 0 }
    , _color{ BLACK, WHITE }
    , _sizeBehaviour{ SizeBehaviour::CONTENT }
    , _visible{ true }
{}

void GUIComponent::SetParent(Window& window) {
    _parent = &window;
}

Window& GUIComponent::GetParent() {
    return *_parent;
}

void GUIComponent::SetPosition(TefkCoord pos) { 
    _pos = pos;
}

TefkCoord GUIComponent::GetPosition() {
    return _pos;
}

void GUIComponent::SetWidth(TefkCoordSizeT width) {
    _size.X = width;
}

TefkCoordSizeT GUIComponent::GetWidth() {
    return _size.X;
}

void GUIComponent::SetHeight(TefkCoordSizeT height) {
    _size.Y = height;
}

TefkCoordSizeT GUIComponent::GetHeight() {
    return _size.Y;
}

TefkCoord GUIComponent::GetContentSize() {
    return { GetContentWidth(), GetContentHeight() };
}

void GUIComponent::SetSizeBehaviour(SizeBehaviour sizeBehaviour) {
    _sizeBehaviour = sizeBehaviour;
}

SizeBehaviour GUIComponent::GetSizeBehaviour() {
    return _sizeBehaviour;
}

void GUIComponent::SetColor(TextColor color) { 
    _color = color; 
}

TextColor GUIComponent::GetColor() {
    return _color;
}

void GUIComponent::SetVisibility(bool visible) {
    _visible = visible;
}

bool GUIComponent::IsVisible() {
    return _visible;
}

bool GUIComponent::Focused() {
    return this == &_parent->GetFocusedComponent();
}

Canvas& GUIComponent::GetCanvas() {
    return _parent->GetCanvas();
}

void GUIComponent::DrawOnCanvas() {
    PixelVector pixelVec;
    pixelVec.resize(_size.Area(), Pixel(' ', _color));
    GetPixelVector(pixelVec);

    for (size_t i = 0; i < pixelVec.size(); i++)
        GetCanvas().PixelAt(i % _size.X + _pos.X, i / _size.X + _pos.Y) = pixelVec[i];
}

} // namespace tefk
