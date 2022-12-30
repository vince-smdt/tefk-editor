#pragma once
#include "consoleapi.hpp"
#include "../logger.hpp"

namespace tefk {

class ConsoleManager {
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static int s_currRows;
	static int s_currCols;
public:
	static bool ConsoleSizeChanged();
	static void ResizeConsole();
};

}