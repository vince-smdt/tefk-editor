#include "color.hpp"

namespace tefk {

TextColor::TextColor() 
	: _fg{ DEFAULT }
	, _bg{ DEFAULT }
{}

TextColor::TextColor(Color fg, Color bg) 
	: _fg{ fg }
	, _bg{ bg }
{}

int TextColor::Foreground() {
	return _fg;
}

int TextColor::Background() {
	return _bg + 10;
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