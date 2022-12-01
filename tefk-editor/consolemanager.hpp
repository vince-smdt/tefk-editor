#pragma once
#include <iostream>
#include "editor.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static CONSOLE_SCREEN_BUFFER_INFO _csbi;
	static int _currRows;
	static int _currCols;
public:
	static int Rows() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Bottom - _csbi.srWindow.Top + 1;
	}

	static int Columns() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Right - _csbi.srWindow.Left + 1;
	}

	static bool ConsoleSizeChanged() {
		return _currRows != Rows() || _currCols != Columns();
	}

	static void RefreshConsole() {
		_currRows = Rows();
		_currCols = Columns();

		system("cls");
		std::cout
			<< Editor::CurrentFile().GetFilename() << " " << Editor::FileIndex() + 1 << "/" << Editor::Files().size()
			<< std::endl << std::endl
			<< Editor::CurrentFile().GetContent()
			<< std::endl << std::endl
			<< "Rows = " << ConsoleManager::Rows() << ", Cols = " << ConsoleManager::Columns();
	}
};
CONSOLE_SCREEN_BUFFER_INFO ConsoleManager::_csbi;
int ConsoleManager::_currRows = 0;
int ConsoleManager::_currCols = 0;

}