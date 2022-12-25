#include "window.hpp"

namespace tefk {

void Window::AddComponent(std::shared_ptr<GUIComponent> component) {
	_children.push_back(std::move(component));
}

void Window::Print() {
	for (auto& child : _children)
		child->Print();
}

}