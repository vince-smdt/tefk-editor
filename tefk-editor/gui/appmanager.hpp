#pragma once
#include <conio.h>
#include <memory>
#include <queue>
#include <stack>

#include "components/window.hpp"
#include "consolemanager.hpp"
#include "input.hpp"

namespace tefk {

class ApplicationManager {
	static std::stack<Window*> s_windows;
	static std::queue<std::shared_ptr<Event>> s_events;
public:
	static void Display();

	static void OpenWindow(Window& window);
	static void CloseWindow();

	static void CatchEvents();
	static void AddEvent(Event event);
	static void RunEvents();
	static void ProcessEvent(Event& event);

	static void CloseApp();
};

} // namespace tefk