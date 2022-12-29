#pragma once
#include <vector>
#include "guicomponent.hpp"

namespace tefk {

class Window {
	std::vector<GUIComponent*> _children;
public:
	void AddComponent(GUIComponent& component);
	void Print();

	virtual void Update() {};
};

}