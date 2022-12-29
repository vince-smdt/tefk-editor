#pragma once
#include <vector>
#include "guicomponent.hpp"

namespace tefk {

class Window {
	std::vector<std::shared_ptr<GUIComponent>> _children;
public:
	void AddComponent(std::shared_ptr<GUIComponent> component);
	void Print();

	virtual void Update() {};
};

}