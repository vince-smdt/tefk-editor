#pragma once
#include <iostream>
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
public:
	Panel(COORD pos, COORD size, TextColor color)
		: GUIComponent(pos, size, color)
	{}

	void Print() {
		ConsoleAPI::SetTextColor(_color);

		for (SHORT currRow = 0; currRow < _size.Y; currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(_size.X, ' ');
		}
	}
};

}