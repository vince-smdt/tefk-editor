#pragma once

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

typedef struct TextColor {
	WinConsoleTextColor bgColor; // background color
	WinConsoleTextColor fgColor; // foreground color

	TextColor Inverse() {
		return { fgColor, bgColor };
	}
} TextColor;