#pragma once
#include "designer/editor.designer.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static int s_currRows;
	static int s_currCols;

	static std::shared_ptr<Window> s_window;
public:
	static void Init();
	static bool ConsoleSizeChanged();
	static void RefreshConsole();
};

}