#include "window.hpp"

namespace tefk {

void Window::AddComponent(GUIComponent& component) {
	_children.push_back(&component);
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
		component->SetWidth(ConsoleAPI::ColCount());

	// HEIGHT
	short availableSpace = ConsoleAPI::RowCount();
	std::list<GUIComponent*> fillComponents;

	// Update components with fixed height
	// Store pointers of components with relative height
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

	// Update height of components with relative heights
	for (auto component : fillComponents)
		component->SetHeight(availableSpace / fillComponents.size());

	// Position every component vertically
	short offsetY = 0;
	for (auto component : visibleComponents) {
		component->SetPosition({ 0, offsetY });
		offsetY += component->GetHeight();
	}
}

void Window::Render() {
	GetCanvas().Resize(ConsoleAPI::ColCount(), ConsoleAPI::RowCount());
	for (auto& child : _children)
		if (child->IsVisible())
			child->DrawOnCanvas();
	GetCanvas().Render();
}

void Window::CatchAndPropagateEvent(Event& event) {
	CatchEvent(event);
	for (auto& child : _children)
		child->CatchEvent(event);
}

} // namespace tefk