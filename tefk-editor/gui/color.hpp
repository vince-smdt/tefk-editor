#pragma once
#include <cassert>
#include <stdint.h>

#define MAX_COLOR_VALUE 0xFFFFFF

namespace tefk {

enum ColorSet {
    BLACK =             0x000000,
    LIGHT_BLACK =       0xAAAAAA,
    RED =               0xBB0000,
    LIGHT_RED =         0xFF0000,
    GREEN =             0x00BB00,
    LIGHT_GREEN =       0x00FF00,
    BLUE =              0x0000BB,
    LIGHT_BLUE =        0x0000FF,
    YELLOW =            0xBBBB00,
    LIGHT_YELLOW =      0xFFFF00,
    MAGENTA =           0xBB00BB,
    LIGHT_MAGENTA =     0xFF00FF,
    CYAN =              0x00BBBB,
    LIGHT_CYAN =        0x00FFFF,
    WHITE =             0xBBBBBB,
    LIGHT_WHITE =       0xFFFFFF
};

struct Color {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;

    Color(unsigned char red, unsigned char green, unsigned char blue);
    Color(uint32_t hex);

    bool operator==(const Color& color);
    bool operator!=(const Color& color);
};

class TextColor {
    Color _fg; // background color
    Color _bg; // foreground color
public:
    TextColor();
    TextColor(Color fg, Color bg);

    Color Foreground();
    Color Background();
    TextColor Inverse();

    bool operator==(const TextColor& textcolor);
    bool operator!=(const TextColor& textcolor);
};

} // namespace tefk
