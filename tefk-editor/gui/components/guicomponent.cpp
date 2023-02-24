#include "guicomponent.hpp"

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

void GUIComponent::SetPosition(Coord pos) { 
    _pos = pos;
}

Coord GUIComponent::GetPosition() {
    return _pos;
}

void GUIComponent::SetWidth(short width) {
    _size.X = width;
}

short GUIComponent::GetWidth() {
    return _size.X;
}

void GUIComponent::SetHeight(short height) {
    _size.Y = height;
}

short GUIComponent::GetHeight() {
    return _size.Y;
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
    pixelVec.resize(_size.Area());
    GetPixelVector(pixelVec);

    for (size_t i = 0; i < pixelVec.size(); i++)
        GetCanvas().PixelAt(i % _size.X + _pos.X, i / _size.X + _pos.Y) = pixelVec[i];
}

} // namespace tefk
