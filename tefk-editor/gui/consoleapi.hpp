#pragma once
#include <conio.h>
#include <Windows.h>

#include "color.hpp"
#include "../logger.hpp" // TODO - maybe move logger inside gui, own folder/projet? (remove gui folder dependency on external file)

namespace tefk {

typedef struct {
	short X;
	short Y;
} Coord;

class ConsoleAPI {
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
public:
	static void Init();
	static short RowCount();
	static short ColCount();
	static short CursorRowPos();
	static short CursorColPos();

	static void SetCursorPos(short row, short col);
	static void SetTextColor(TextColor color);
	static void SetConsoleSize(short row, short col);

	static void HideCursor();

	static unsigned char ReadKeypress();
private:
	static void GetConsoleBufferInfo();
};

} // namespace tefk