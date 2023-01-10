#pragma once

namespace tefk {

enum Color {
	DEFAULT = 0,
	BLACK = 30,
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37,
	LIGHT_BLACK = 90,
	LIGHT_RED = 91,
	LIGHT_GREEN = 92,
	LIGHT_YELLOW = 93,
	LIGHT_BLUE = 94,
	LIGHT_MAGENTA = 95,
	LIGHT_CYAN = 96,
	LIGHT_WHITE = 97
};

class TextColor {
	Color _fg; // background color
	Color _bg; // foreground color
public:
	TextColor();
	TextColor(Color fg, Color bg);

	int Foreground();
	int Background();
	TextColor Inverse();

	bool operator==(const TextColor& textcolor);
	bool operator!=(const TextColor& textcolor);
};

} // namespace tefk