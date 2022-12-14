#pragma once
#include <Windows.h>
#include "logger.hpp"

namespace tefk {

// TODO - Move this to another file
enum WinConsoleTextColor {
	BLACK = 0x00,
	BLUE = 0x01,
	GREEN = 0x02,
	AQUA = 0x03,
	RED = 0x04,
	PURPLE = 0x05,
	YELLOW = 0x06,
	WHITE = 0x07,
	GRAY = 0x08,
	LIGHT_BLUE = 0x09,
	LIGHT_GREEN = 0x0a,
	LIGHT_AQUA = 0x0b,
	LIGHT_RED = 0x0c,
	LIGHT_PURPLE = 0x0d,
	LIGHT_YELLOW = 0x0e,
	BRIGHT_WHITE = 0x0f,
};

// TODO - Move this to another file
typedef struct TextColor {
	WinConsoleTextColor backgroundColor;
	WinConsoleTextColor foregroundColor;
} TextColor;

class ConsoleAPI {
private:
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
public:
	static int RowCount() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1;
	}

	static int ColCount() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1;
	}

	static int CursorRowPos() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.dwCursorPosition.Y;
	}

	static int CursorColPos() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.dwCursorPosition.X;
	}

	static void SetCursorPos(SHORT row, SHORT col) {
		COORD pos = { col, row };
		SetConsoleCursorPosition(s_handle, pos);
	}

	static void SetTextColor(TextColor color) {
		int colorCode = color.foregroundColor + color.backgroundColor * 0x10;
		SetConsoleTextAttribute(s_handle, colorCode);
	}

	static void SetConsoleSize(SHORT row, SHORT col) {
		COORD size = { col, row };
		if (!SetConsoleScreenBufferSize(s_handle, size)) {
			Logger::Instance().Log("SetConsoleScreenBufferSize() failed! Reason : {}", GetLastError());
			exit(0);
		}
	}
};
HANDLE ConsoleAPI::s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleAPI::s_csbi;

}