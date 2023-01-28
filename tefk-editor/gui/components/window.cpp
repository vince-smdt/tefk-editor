#include "window.hpp"

namespace tefk {

Window::Window()
	: _isClosing{ false },
	  _focusedComponent{ nullptr }
{}

GUIComponent& Window::GetFocusedComponent() {
	return *_focusedComponent;
}

void Window::AddComponent(GUIComponent& component) {
	// TODO - check if component already has a parent
	_children.push_back(&component);
	component.SetParent(*this);
}

// TODO - avoid giving negative values to components height
void Window::UpdateComponents() {
	// Select visible components
	std::list<GUIComponent*> visibleComponents;

	for (auto component : _children)
		if (component->IsVisible())
			visibleComponents.push_back(component);

	// Update component properties

	// WIDTH
	for (auto component : visibleComponents)
		component->SetWidth(ConsoleAPI::GetConsoleSize().X);

	// HEIGHT
	short availableSpace = ConsoleAPI::GetConsoleSize().Y;
	std::list<GUIComponent*> fillComponents;

	// Update content height components
	// Store pointers of fill height components
	for (auto component : visibleComponents) {
		// TODO - update height in separate function (maybe do same for width)
		switch (component->GetHeightBehaviour()) {
		case SizeBehaviour::CONTENT: {
			size_t contentSize = component->GetContent().size();
			short divider = component->GetWidth() == 0 ? contentSize : component->GetWidth();

			component->SetHeight((short)ceil(double(contentSize) / divider));
			availableSpace -= component->GetHeight();
			break;
		}
		case SizeBehaviour::FILL:
			fillComponents.push_back(component);
			break;
		}
	}

	// Update height of fill height components
	short fillHeight = availableSpace / fillComponents.size();
	short leftoverSpace = availableSpace % fillComponents.size();
	for (auto component : fillComponents) {
		if (component != fillComponents.back())
			component->SetHeight(fillHeight);
		else
			component->SetHeight(fillHeight + leftoverSpace);
	}

	// Position every component vertically
	short offsetY = 0;
	for (auto component : visibleComponents) {
		component->SetPosition({ 0, offsetY });
		offsetY += component->GetHeight();
	}
}

void Window::Render() {
	GetCanvas().Resize(ConsoleAPI::GetConsoleSize().X, ConsoleAPI::GetConsoleSize().Y);
	for (auto& child : _children)
		if (child->IsVisible())
			child->DrawOnCanvas();
	GetCanvas().Render();
}

void Window::Focus(GUIComponent& component) {
	_focusedComponent = &component;
}

void Window::Close() {
	_isClosing = true;
}

bool Window::IsClosing() {
	return _isClosing;
}

void Window::CatchAndPropagateEvent(Event event) {
	CatchEvent(event);
	for (auto& child : _children)
		child->CatchEvent(event);
}

} // namespace tefk