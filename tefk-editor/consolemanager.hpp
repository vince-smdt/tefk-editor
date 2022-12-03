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

	// TODO - Move this enum to some other file
	enum WinConsoleTextColor {
		BLACK =			0x00,
		BLUE =			0x01,
		GREEN =			0x02,
		AQUA =			0x03,
		RED =			0x04,
		PURPLE =		0x05,
		YELLOW =		0x06,
		WHITE =			0x07,
		GRAY =			0x08,
		LIGHT_BLUE =	0x09,
		LIGHT_GREEN =	0x0a,
		LIGHT_AQUA =	0x0b,
		LIGHT_RED =		0x0c,
		LIGHT_PURPLE =	0x0d,
		LIGHT_YELLOW =	0x0e,
		BRIGHT_WHITE =	0x0f,
	};
public:
	// TODO - Find way to avoid redundant GetConsoleScreenBufferInfo function calls, decorators?
	// TODO - Make GetStdHandle(STD_OUTPUT_HANDLE) into a constant if it doesn't change during runtime
	static int RowCount() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Bottom - _csbi.srWindow.Top + 1;
	}

	static int ColCount() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.srWindow.Right - _csbi.srWindow.Left + 1;
	}

	static int CursorRowPos() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.dwCursorPosition.Y;
	}

	static int CursorColPos() {
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
		return _csbi.dwCursorPosition.X;
	}

	static bool ConsoleSizeChanged() {
		return _currRows != RowCount() || _currCols != ColCount();
	}

	static void SetCursorPos(int row, int col) {
		COORD pos = { col, row };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	static void SetTextColor(WinConsoleTextColor backgroundColor, WinConsoleTextColor foregroundColor) {
		int color = foregroundColor + backgroundColor * 0x10;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	static void PrintHeader() {
		// TODO - Only print content that fits in the console, rest can be seen by scrolling
		SetTextColor(WHITE, BLACK);
		SetCursorPos(0, 0);
		std::cout
			<< Editor::CurrentFile().GetFilename() << " "
			<< Editor::FileIndex() + 1 << "/"
			<< Editor::Files().size();
		FillRow();
		SetTextColor(BLACK, WHITE);
	}

	static void PrintContent() {
		SetCursorPos(2, 0);
		std::cout << Editor::CurrentFile().GetContent();
	}

	static void PrintFooter() {
		SetTextColor(WHITE, BLACK);
		SetCursorPos(RowCount() - 1, 0);
		std::cout << "Rows = " << ConsoleManager::RowCount() << ", Cols = " << ConsoleManager::ColCount();
		FillRow();
		SetTextColor(BLACK, WHITE);
	}

	static void FillRow() {
		std::cout << std::string(ColCount() - CursorColPos(), ' ');
	}

	static void RefreshConsole() {
		// TODO - Reset entire console color in case previous color before app starts
		_currRows = RowCount();
		_currCols = ColCount();

		COORD consoleSize;
		consoleSize.X = _currCols;
		consoleSize.Y = _currRows;
		if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), consoleSize)) {
			// TODO - Proper error handling / implement log system?
			std::cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
			exit(0);
		}

		// TODO - Code more efficient function to clear console
		system("cls");

		PrintHeader();
		PrintContent();
		PrintFooter();
	}
};
CONSOLE_SCREEN_BUFFER_INFO ConsoleManager::_csbi;
int ConsoleManager::_currRows = 0;
int ConsoleManager::_currCols = 0;

}