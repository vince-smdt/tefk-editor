#pragma once
#include <cassert>
#include <conio.h>
#include <Windows.h>

#include "color.hpp"
#include "../logger.hpp" // TODO - maybe move logger inside gui, own folder/projet? (remove gui folder dependency on external file)

namespace tefk {

struct Coord {
	short X;
	short Y;

	short Area() {
		return X * Y;
	}

	bool operator==(const Coord& c) {
		return X == c.X && Y == c.Y;
	}

	bool operator!=(const Coord& c) {
		return X != c.X || Y != c.Y;
	}
};

class ConsoleAPI {
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
	static Coord s_lastRecordedSize;
public:
	static void Init();

	static bool ConsoleSizeChanged();
	static Coord GetConsoleSize();
	static void UpdateConsoleSize();

	static unsigned char ReadKeypress();
private:
	static void GetConsoleBufferInfo();
};

} // namespace tefk