#pragma once
#include <vector>

#include "../event.hpp"
#include "guicomponent.hpp"

namespace tefk {

class Window {
	bool _isClosing;
	GUIComponent* _focusedComponent;
	std::vector<GUIComponent*> _children;
public:
	Window();

	void AddComponent(GUIComponent& component);
	void UpdateComponents();
	void Render();
	void Focus(GUIComponent& component);
	void Close();

	bool IsClosing();

	void CatchAndPropagateEvent(Event event);
	virtual void CatchEvent(Event event) {};
};

} // namespace tefk