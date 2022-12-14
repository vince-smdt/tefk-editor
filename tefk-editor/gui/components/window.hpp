#pragma once
#include <vector>

#include "../event.hpp"
#include "guicomponent.hpp"

namespace tefk {

class Window {
	std::vector<GUIComponent*> _children;
public:
	void AddComponent(GUIComponent& component);
	void UpdateComponents();
	void Render();
	void CatchAndPropagateEvent(Event& event);

	virtual void CatchEvent(Event& event) {};
};

} // namespace tefk