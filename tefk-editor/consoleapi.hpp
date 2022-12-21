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
	static void GetConsoleBufferInfo();
	static short RowCount();
	static short ColCount();
	static short CursorRowPos();
	static short CursorColPos();

	static void SetCursorPos(short row, short col);
	static void SetTextColor(TextColor color);
	static void SetConsoleSize(short row, short col);

	static void ClearConsole();
};

}