#pragma once
#include <Windows.h>
#include "color.h"
#include "logger.hpp"

namespace tefk {

class ConsoleAPI {
private:
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
public:
	static SHORT RowCount() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1;
	}

	static SHORT ColCount() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1;
	}

	static SHORT CursorRowPos() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.dwCursorPosition.Y;
	}

	static SHORT CursorColPos() {
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		return s_csbi.dwCursorPosition.X;
	}

	static void SetCursorPos(SHORT row, SHORT col) {
		COORD pos = { col, row };
		SetConsoleCursorPosition(s_handle, pos);
	}

	static void SetTextColor(TextColor color) {
		int colorCode = color.fgColor + color.bgColor * 0x10;
		SetConsoleTextAttribute(s_handle, colorCode);
	}

	static void SetConsoleSize(SHORT row, SHORT col) {
		COORD size = { col, row };
		if (!SetConsoleScreenBufferSize(s_handle, size)) {
			Logger::Instance().Log("SetConsoleScreenBufferSize() failed! Reason : {}", GetLastError());
			exit(0);
		}
	}

	static void ClearConsole() {
		DWORD written;

		SetTextColor({ BLACK, WHITE }); // Get default text color from variable
		GetConsoleScreenBufferInfo(s_handle, &s_csbi);
		FillConsoleOutputCharacterA(
			s_handle, ' ', s_csbi.dwSize.X * s_csbi.dwSize.Y, {0, 0}, &written
		);
		FillConsoleOutputAttribute(
			s_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			s_csbi.dwSize.X * s_csbi.dwSize.Y, {0, 0}, &written
		);
		SetCursorPos(0, 0);
	}
};
HANDLE ConsoleAPI::s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleAPI::s_csbi;

}