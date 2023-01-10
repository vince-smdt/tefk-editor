#include "window.hpp"

namespace tefk {

void Window::AddComponent(GUIComponent& component) {
	_children.push_back(&component);
}

void Window::UpdateComponents() {
	short availableSpace = ConsoleAPI::RowCount();
	std::list<GUIComponent*> fillComponents;

	// Update components with fixed height
	// Store pointers of components with relative height
	for (auto component : _children) {
		switch (component->GetHeightBehaviour()) {
		case SizeBehaviour::CONTENT:
			availableSpace -= component->UpdateHeight();
			break;
		case SizeBehaviour::FILL:
			fillComponents.push_back(component);
			break;
		}
	}

	// Update height of components with relative heights
	for (auto component : fillComponents)
		component->SetHeight(availableSpace / fillComponents.size());

	// Position every component vertically
	short offsetY = 0;
	for (auto component : _children) {
		component->SetPosition({ 0, offsetY });
		offsetY += component->GetHeight();
	}
}

void Window::Render() {
	Canvas::Instance().Resize(ConsoleAPI::ColCount(), ConsoleAPI::RowCount());
	for (auto& child : _children)
		child->Render();
	std::cout.flush();
}

void Window::CatchAndPropagateEvent(Event& event) {
	CatchEvent(event);
	for (auto& child : _children)
		child->CatchEvent(event);
}

} // namespace tefk