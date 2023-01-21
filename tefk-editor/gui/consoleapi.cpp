#include "consoleapi.hpp"

namespace tefk {

HANDLE ConsoleAPI::s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleAPI::s_csbi;
int ConsoleAPI::s_currRows = 0;
int ConsoleAPI::s_currCols = 0;

void ConsoleAPI::Init() {
	// Disable Ctrl+C closing app
	SetConsoleCtrlHandler(NULL, TRUE);

	// Activate Virtual Terminal Sequences
	DWORD prevMode;
	HANDLE hInput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hInput, &prevMode);
	SetConsoleMode(hInput, prevMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

bool ConsoleAPI::ConsoleSizeChanged() {
	return s_currRows != ConsoleAPI::GetConsoleSize().Y || s_currCols != ConsoleAPI::GetConsoleSize().X;
}

void ConsoleAPI::ResizeConsole() {
	s_currRows = ConsoleAPI::GetConsoleSize().Y;
	s_currCols = ConsoleAPI::GetConsoleSize().X;

	ConsoleAPI::SetConsoleSize(s_currRows, s_currCols);
}

Coord ConsoleAPI::GetConsoleSize() {
	GetConsoleBufferInfo();
	return Coord(
		s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1,
		s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1
	);
}

void ConsoleAPI::SetConsoleSize(short row, short col) {
	COORD size = { col, row };
	if (!SetConsoleScreenBufferSize(s_handle, size)) {
		Logger::Instance().Log(
			Logger::LogLevel::ERR,
			"SetConsoleScreenBufferSize() failed! Reason : {}", 
			GetLastError()
		);
		exit(0);
	}
}

unsigned char ConsoleAPI::ReadKeypress() {
	return _getch();
}

void ConsoleAPI::GetConsoleBufferInfo() {
	if (!GetConsoleScreenBufferInfo(s_handle, &s_csbi)) {
		Logger::Instance().Log(
			Logger::LogLevel::ERR,
			"GetConsoleBufferInfo() failed! Reason : {}", 
			GetLastError()
		);
		exit(0);
	}
}

} // namespace tefk