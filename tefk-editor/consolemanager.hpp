#pragma once
#include <iostream>
#include "editor.hpp"
#include "logger.hpp"

namespace tefk {

class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static HANDLE _handle;
	static CONSOLE_SCREEN_BUFFER_INFO _csbi;
	static int _currRows;
	static int _currCols;

	// TODO - Move this enum to some other file
	enum WinConsoleTextColor {
		BLACK =         0x00,
		BLUE =          0x01,
		GREEN =         0x02,
		AQUA =          0x03,
		RED =           0x04,
		PURPLE =        0x05,
		YELLOW =        0x06,
		WHITE =         0x07,
		GRAY =          0x08,
		LIGHT_BLUE =    0x09,
		LIGHT_GREEN =   0x0a,
		LIGHT_AQUA =    0x0b,
		LIGHT_RED =     0x0c,
		LIGHT_PURPLE =  0x0d,
		LIGHT_YELLOW =  0x0e,
		BRIGHT_WHITE =  0x0f,
	};

	typedef struct TextColor {
		WinConsoleTextColor backgroundColor;
		WinConsoleTextColor foregroundColor;
	} TextColor;

public:
	// TODO - Find way to avoid redundant GetConsoleScreenBufferInfo function calls, decorators?
	static int RowCount() {
		GetConsoleScreenBufferInfo(_handle, &_csbi);
		return _csbi.srWindow.Bottom - _csbi.srWindow.Top + 1;
	}

	static int ColCount() {
		GetConsoleScreenBufferInfo(_handle, &_csbi);
		return _csbi.srWindow.Right - _csbi.srWindow.Left + 1;
	}

	static int CursorRowPos() {
		GetConsoleScreenBufferInfo(_handle, &_csbi);
		return _csbi.dwCursorPosition.Y;
	}

	static int CursorColPos() {
		GetConsoleScreenBufferInfo(_handle, &_csbi);
		return _csbi.dwCursorPosition.X;
	}

	static bool ConsoleSizeChanged() {
		return _currRows != RowCount() || _currCols != ColCount();
	}

	static void SetCursorPos(int row, int col) {
		COORD pos = { col, row };
		SetConsoleCursorPosition(_handle, pos);
	}

	static void SetTextColor(TextColor color) {
		int colorCode = color.foregroundColor + color.backgroundColor * 0x10;
		SetConsoleTextAttribute(_handle, colorCode);
	}

	static void Print(std::string text, TextColor color = { BLACK, WHITE }) {
		SetTextColor(color);

		if (text.size() > ColCount())
			text = text.substr(0, ColCount() - 1);
		std::cout << text << FillRow;

		SetTextColor({ BLACK, WHITE });
	}

	static void PrintHeader() {
		SetCursorPos(0, 0);

		std::stringstream ss;
		ss << Editor::CurrentFile().GetFilename() << " "
		   << Editor::FileIndex() + 1 << "/"
		   << Editor::Files().size();
		Print(ss.str(), { WHITE, BLACK });
	}

	static void PrintContent() {
		// TODO - Only print content that fits in the console, rest can be seen by scrolling
		SetCursorPos(2, 0);

		std::stringstream ss;
		ss << Editor::CurrentFile().GetContent();
		Print(ss.str());
	}

	static void PrintFooter() {
		SetCursorPos(RowCount() - 1, 0);

		std::stringstream ss;
		ss << "Rows = " << ConsoleManager::RowCount() 
		   << ", Cols = " << ConsoleManager::ColCount();
		Print(ss.str(), { WHITE, BLACK });
	}

	static std::ostream& FillRow(std::ostream& stream) {
		return stream << std::string(ColCount() - CursorColPos(), ' ');
	}

	static void RefreshConsole() {
		// TODO - Reset entire console color in case previous color before app starts
		_currRows = RowCount();
		_currCols = ColCount();

		COORD consoleSize = { _currCols, _currRows };
		if (!SetConsoleScreenBufferSize(_handle, consoleSize)) {
			// TODO - make logger callable from anywhere without having to initialize logger object
			Logger::Instance().Log("SetConsoleScreenBufferSize() failed! Reason : {}", GetLastError());
			exit(0);
		}

		// TODO - Code more efficient function to clear console
		system("cls");

		PrintHeader();
		PrintContent();
		PrintFooter();
	}
};
HANDLE ConsoleManager::_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleManager::_csbi;
int ConsoleManager::_currRows = 0;
int ConsoleManager::_currCols = 0;

}