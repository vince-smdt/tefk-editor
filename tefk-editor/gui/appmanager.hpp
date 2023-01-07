#pragma once
#include <conio.h>
#include <memory>
#include <queue>
#include <stack>

#include "components/window.hpp"
#include "consolemanager.hpp"
#include "input.hpp"
#include "canvas.hpp"

namespace tefk::ApplicationManager {
	namespace {
		Canvas _screen;
		std::stack<Window*> _windows;
		std::queue<std::shared_ptr<Event>> _events;
	}

	void Display();

	void OpenWindow(Window& window);
	void CloseWindow();

	void CatchEvents();
	void AddEvent(Event event);
	void RunEvents();
	void ProcessEvent(Event& event);

	void CloseApp();
} // namespace tefk::ApplicationManager