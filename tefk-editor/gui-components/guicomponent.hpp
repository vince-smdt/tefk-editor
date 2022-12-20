#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class GUIComponent : public std::enable_shared_from_this<GUIComponent> {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	std::shared_ptr<GUIComponent> _parent;
	std::vector<std::shared_ptr<GUIComponent>> _children;
	
	const Coord _ORIGIN = { 0, 0 };

	typedef std::shared_ptr<GUIComponent> GUIComponentPtr;
public:
	GUIComponent()
		: _pos{ _ORIGIN },
		  _size{ _ORIGIN },
		  _color{ BLACK, BLACK } // TODO - set to default component color?
	{}

	Coord GetPosition() { return _pos; }
	Coord GetSize() { return _size; }
	TextColor GetColor() { return _color; }
	GUIComponentPtr GetParent() { return _parent; }
	std::vector<GUIComponentPtr>& GetChildren() { return _children; }

	void SetPosition(Coord pos) { _pos = pos; }
	void SetSize(Coord size) { _size = size; }
	void SetColor(TextColor color) { _color = color; }
	void SetParent(GUIComponentPtr component) { _parent = component; }

	// TODO - prevent circular parent/child connections
	void AddComponent(GUIComponentPtr component) {
		// Check if component is already a child of this component
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
	
	virtual void Print() {}
};

}
