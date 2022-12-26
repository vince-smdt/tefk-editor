#pragma once
#include "components/window.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static int s_currRows;
	static int s_currCols;

	static std::shared_ptr<Window> s_window;
public:
	static void Init(std::shared_ptr<Window> window); // TODO - set target window in some other place than the constructor
	static bool ConsoleSizeChanged();
	static void RefreshConsole();
};

}