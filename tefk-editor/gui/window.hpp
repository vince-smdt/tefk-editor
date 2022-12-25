#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Window {
private:
	std::vector<std::shared_ptr<GUIComponent>> _children;
public:
	void AddComponent(std::shared_ptr<GUIComponent> component);
	void Print();
};

}