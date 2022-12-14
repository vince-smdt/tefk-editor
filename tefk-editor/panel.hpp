#pragma once
#include <iostream>
#include <Windows.h>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class Panel {
private:
	COORD _pos;
	COORD _size;
	TextColor _color;
public:
	Panel(COORD pos, COORD size, TextColor color) 
		: _pos{pos},
		  _size{size},
		  _color{color}
	{}

	void Print() {
		ConsoleAPI::SetTextColor(_color);

		for (SHORT currRow = 0; currRow < _size.Y; currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(_size.X, ' ');
		}

		ConsoleAPI::SetTextColor({BLACK, WHITE});
	}
};

}