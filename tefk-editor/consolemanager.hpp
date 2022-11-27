#pragma once
#include <Windows.h>
#include "editor.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static CONSOLE_SCREEN_BUFFER_INFO _csbi;
public:
	static int Rows() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Bottom - _csbi.srWindow.Top + 1;
	}

	static int Columns() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Right - _csbi.srWindow.Left + 1;
	}
};
CONSOLE_SCREEN_BUFFER_INFO ConsoleManager::_csbi;

}