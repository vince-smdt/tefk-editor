#pragma once
#include <conio.h>
#include <memory>
#include <queue>
#include <stack>

#include "canvas.hpp"
#include "components/window.hpp"
#include "input.hpp"

namespace tefk::ApplicationManager {
	namespace {
		bool _running = true;
		std::stack<Window*> _windows;
		std::queue<std::shared_ptr<Event>> _events;
	}

	void Render();

	void OpenWindow(Window& window);
	void CloseWindow();

	void CatchEvents();
	void AddEvent(Event event);
	void RunEvents();
	void ProcessEvent(Event event);

	bool Running();

	void CloseApp();
} // namespace tefk::ApplicationManager