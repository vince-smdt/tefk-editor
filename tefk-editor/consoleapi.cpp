#include "consoleapi.hpp"

namespace tefk {

HANDLE ConsoleAPI::s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleAPI::s_csbi;

void ConsoleAPI::GetConsoleBufferInfo() {
	if (!GetConsoleScreenBufferInfo(s_handle, &s_csbi)) {
		Logger::Instance().Log("GetConsoleBufferInfo() failed! Reason : {}", GetLastError());
		exit(0);
	}
}

short ConsoleAPI::RowCount() {
	GetConsoleBufferInfo();
	return s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1;
}

short ConsoleAPI::ColCount() {
	GetConsoleBufferInfo();
	return s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1;
}

short ConsoleAPI::CursorRowPos() {
	GetConsoleBufferInfo();
	return s_csbi.dwCursorPosition.Y;
}

short ConsoleAPI::CursorColPos() {
	GetConsoleBufferInfo();
	return s_csbi.dwCursorPosition.X;
}

void ConsoleAPI::SetCursorPos(short row, short col) {
	COORD pos = { col, row };
	if (!SetConsoleCursorPosition(s_handle, pos)) {
		Logger::Instance().Log("SetConsoleCursorPosition() failed! Position : ({}, {}), Reason : {}", pos.X, pos.Y, GetLastError());
		exit(0);
	}
}

void ConsoleAPI::SetTextColor(TextColor color) {
	WORD colorCode = color.fgColor + color.bgColor * 0x10;
	if (!SetConsoleTextAttribute(s_handle, colorCode)) {
		Logger::Instance().Log("SetConsoleTextAttribute() failed! Reason : {}", GetLastError());
		exit(0);
	}
}

void ConsoleAPI::SetConsoleSize(short row, short col) {
	COORD size = { col, row };
	if (!SetConsoleScreenBufferSize(s_handle, size)) {
		Logger::Instance().Log("SetConsoleScreenBufferSize() failed! Reason : {}", GetLastError());
		exit(0);
	}
}

}