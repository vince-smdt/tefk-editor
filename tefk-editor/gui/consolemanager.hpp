#pragma once
#include <stack>
#include "components/window.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static int s_currRows;
	static int s_currCols;

	static std::stack<Window*> s_windows;
public:
	static void OpenWindow(Window& window);
	static void CloseWindow();
	static void CloseApp(); // TODO - maybe move this in App class, close app in more appropriate place?
	static bool ConsoleSizeChanged();
	static void RefreshConsole();
};

}