#pragma once
#include <system_error>
#include <Windows.h>
#include "color.h"
#include "logger.hpp"

namespace tefk {

typedef struct {
	short X;
	short Y;
} Coord;

class ConsoleAPI {
private:
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
public:
	static void GetConsoleBufferInfo() {
		if (!GetConsoleScreenBufferInfo(s_handle, &s_csbi)) {
			std::string message = std::system_category().message(GetLastError());
			Logger::Instance().Log("GetConsoleBufferInfo() failed! Reason : {}", message);
			exit(0);
		}
	}

	static short RowCount() {
		GetConsoleBufferInfo();
		return s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1;
	}

	static short ColCount() {
		GetConsoleBufferInfo();
		return s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1;
	}

	static short CursorRowPos() {
		GetConsoleBufferInfo();
		return s_csbi.dwCursorPosition.Y;
	}

	static short CursorColPos() {
		GetConsoleBufferInfo();
		return s_csbi.dwCursorPosition.X;
	}

	static void SetCursorPos(short row, short col) {
		COORD pos = { col, row };
		if (!SetConsoleCursorPosition(s_handle, pos)) {
			std::string message = std::system_category().message(GetLastError());
			Logger::Instance().Log("SetConsoleCursorPosition() failed! Reason : {}", message);
			exit(0);
		}
	}

	static void SetTextColor(TextColor color) {
		WORD colorCode = color.fgColor + color.bgColor * 0x10;
		if (!SetConsoleTextAttribute(s_handle, colorCode)) {
			std::string message = std::system_category().message(GetLastError());
			Logger::Instance().Log("SetConsoleTextAttribute() failed! Reason : {}", message);
			exit(0);
		}
	}

	static void SetConsoleSize(short row, short col) {
		COORD size = { col, row };
		if (!SetConsoleScreenBufferSize(s_handle, size)) {
			std::string message = std::system_category().message(GetLastError());
			Logger::Instance().Log("SetConsoleScreenBufferSize() failed! Reason : {}", message);
			exit(0);
		}
	}

	static void ClearConsole() {
		DWORD written;
		SetTextColor({ BLACK, WHITE }); // TODO - Get default text color from variable
		GetConsoleBufferInfo();

		// TODO - Error check these functions in readable and concise way
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