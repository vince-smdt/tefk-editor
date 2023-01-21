#pragma once
#include <conio.h>
#include <Windows.h>

#include "color.hpp"
#include "../logger.hpp" // TODO - maybe move logger inside gui, own folder/projet? (remove gui folder dependency on external file)

namespace tefk {

typedef struct {
	short X;
	short Y;

	bool operator==(Coord c) {
		return X == c.X && Y == c.Y;
	}

	bool operator!=(Coord c) {
		return X != c.X || Y != c.Y;
	}
} Coord;

class ConsoleAPI {
	ConsoleAPI() = delete;
	ConsoleAPI(const ConsoleAPI&) = delete;

	static HANDLE s_handle;
	static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
	static Coord s_lastRecordedSize;
public:
	static void Init();

	static bool ConsoleSizeChanged();
	static void ResizeConsole();
	static Coord GetConsoleSize();
	static void SetConsoleSize(Coord size);

	static unsigned char ReadKeypress();
private:
	static void GetConsoleBufferInfo();
};

} // namespace tefk