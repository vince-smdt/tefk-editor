#include "color.hpp"

namespace tefk {

Color::Color(unsigned char red, unsigned char green, unsigned char blue)
    : Red{ red }
    , Green{ green }
    , Blue{ blue }
{}

Color::Color(uint32_t hex) {
    assert(hex <= MAX_COLOR_VALUE);
    Red = hex >> 16;                            // 0xABCDEF >> 16 = 0xAB
    Green = (hex >> 8) - (Red << 8);            // (0xABCDEF >> 8) - (0XAB << 8) = 0xABCD - 0xAB00 = 0xCD
    Blue = hex - ((Red << 16) + (Green << 8));  // 0xABCDEF - ((0xAB << 16) + (0xCD << 8)) = 0xABCDEF - (0xAB0000 + 0x00CD00) = 0xEF
}

bool Color::operator==(const Color& color) {
    return Red == color.Red && Green == color.Green && Blue == color.Blue;
}

bool Color::operator!=(const Color& color) {
    return Red != color.Red || Green != color.Green || Blue != color.Blue;
}

TextColor::TextColor() 
    : _fg{ 0, 0, 0 }
    , _bg{ 0, 0, 0 }
{}

TextColor::TextColor(Color fg, Color bg) 
    : _fg{ fg }
    , _bg{ bg }
{}

Color TextColor::Foreground() {
    return _fg;
}

Color TextColor::Background() {
    return _bg;
}

TextColor TextColor::Inverse() {
    return TextColor(_bg, _fg);
}

bool TextColor::operator==(const TextColor& textcolor) {
    return textcolor._fg == _fg && textcolor._bg == _bg;
}

bool TextColor::operator!=(const TextColor& textcolor) {
    return textcolor._fg != _fg || textcolor._bg != _bg;
}

} // tefk namespace
