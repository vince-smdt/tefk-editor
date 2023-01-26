#pragma once
#include <vector>

#include "../event.hpp"
#include "guicomponent.hpp"

namespace tefk {

class Window {
	bool _isClosing;
	std::vector<GUIComponent*> _children;
public:
	Window();

	void AddComponent(GUIComponent& component);
	void UpdateComponents();
	void Render();
	void CatchAndPropagateEvent(Event& event);
	void Close();

	bool IsClosing();

	virtual void CatchEvent(Event& event) {};
};

} // namespace tefk