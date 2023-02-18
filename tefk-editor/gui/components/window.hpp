#pragma once
#include <vector>

#include "../event.hpp"
#include "guicomponent.hpp"

namespace tefk {

class GUIComponent;

class Window {
	std::vector<GUIComponent*> _children;
	GUIComponent* _focusedComponent;
	Canvas _canvas;
	bool _isClosing;
public:
	Window();

	// Actions
	void AddComponent(GUIComponent& component);
	void UpdateComponents();
	void Render();
	void Focus(GUIComponent& component);
	void Close();

	// Properties
	GUIComponent& GetFocusedComponent();
	bool IsClosing();
	Canvas& GetCanvas();

	void CatchAndPropagateEvent(Event event);
	virtual void CatchEvent(Event event) {};
};

} // namespace tefk