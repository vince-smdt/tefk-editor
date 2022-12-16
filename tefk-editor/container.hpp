#pragma once
#include <vector>
#include "guicomponent.hpp"

namespace tefk {

class Container {
protected:
	std::vector<GUIComponent*> _children;
public:
	Container()
		: _children{}
	{}

	// TODO - prevent circular parent/child connections
	void AddComponent(GUIComponent* component) {
		_children.push_back(component);
		component->SetParent(this);
	}
};

}
