#pragma once
#include <Windows.h>
#include "editor.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;
public:
	static int Rows() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

	static int Columns() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
};

}