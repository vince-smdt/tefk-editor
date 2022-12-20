#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Window : public std::enable_shared_from_this<Window> {
private:
	typedef std::shared_ptr<GUIComponent> GUIComponentPtr;

	std::vector<GUIComponentPtr> _children;
public:
	std::vector<GUIComponentPtr>& GetChildren() { return _children; }

	void AddComponent(GUIComponentPtr component) {
		// Check if component is already appart of this window
		if (component->GetParent().get() == this)
			return;

		// Remove component from parent's children vector
		if (component->GetParent()) {
			std::vector<GUIComponentPtr>& children = component->GetParent()->GetChildren();
			children.erase(
				std::remove_if(
					children.begin(),
					children.end(),
					[component](const GUIComponentPtr& child) { return child.get() == component.get(); }
				),
				children.end()
			);
		}

		// Modify ownership
		component->SetParent(shared_from_this());
		_children.push_back(std::move(component));
	}

	void Print() {
		for (auto& child : _children)
			child->Print();
	}
};

}