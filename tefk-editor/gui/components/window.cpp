#include "window.hpp"

namespace tefk {

void Window::AddComponent(GUIComponent& component) {
	_children.push_back(&component);
}

void Window::Print() {
	for (auto& child : _children)
		child->Print();
	std::cout.flush();
}

}