#include "guicomponent.hpp"

namespace tefk {

GUIComponent::GUIComponent(SizeBehaviour heightBehaviour)
	: _parent{ nullptr },
	  _pos{ 0, 0 },
	  _size{ 0, 0 },
	  _color{ BLACK, WHITE },
	  _heightBehaviour{ heightBehaviour },
	  _visible{ true }
{}

void GUIComponent::SetParent(Window& window) {
	_parent = &window;
}

void GUIComponent::SetPosition(Coord pos) { 
	_pos = pos;
}

void GUIComponent::SetWidth(short width) {
	_size.X = width;
}

void GUIComponent::SetHeight(short height) {
	_size.Y = height;
}

void GUIComponent::SetHeight(SizeBehaviour sizeBehaviour) {
	_heightBehaviour = sizeBehaviour;
}

void GUIComponent::SetColor(TextColor color) { 
	_color = color; 
}

void GUIComponent::SetVisible(bool visible) {
	_visible = visible;
}

Window& GUIComponent::GetParent() {
	return *_parent;
}

short GUIComponent::GetWidth() {
	return _size.X;
}

short GUIComponent::GetHeight() {
	return _size.Y;
}

SizeBehaviour GUIComponent::GetHeightBehaviour() {
	return _heightBehaviour;
}

bool GUIComponent::IsVisible() {
	return _visible;
}

bool GUIComponent::Focused() {
	return this == &_parent->GetFocusedComponent();
}

} // namespace tefk