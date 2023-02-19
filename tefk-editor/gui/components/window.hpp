#pragma once
#include <vector>

#include "../event.hpp"
#include "guicomponent.hpp"
#include "../timer.hpp"

namespace tefk {

class GUIComponent;

class Window {
	std::vector<GUIComponent*> _children;
	GUIComponent* _focusedComponent;
	std::vector<std::pair<Timer*, std::function<void()>>> _timerBoundProcedures;
	Canvas _canvas;
	bool _isClosing;
public:
	Window();

	// Actions
	void AddComponent(GUIComponent& component);
	void UpdateComponents();
	void AddTimerBoundProcedure(Timer* timer, std::function<void()> procedure);
	void Render();
	void Focus(GUIComponent& component);
	void Close();

	// Properties
	GUIComponent& GetFocusedComponent();
	bool IsClosing();
	bool ExecuteTimerBoundProcedures();
	Canvas& GetCanvas();

	void CatchAndPropagateEvent(Event event);
	virtual void CatchEvent(Event event) {};
};

} // namespace tefk