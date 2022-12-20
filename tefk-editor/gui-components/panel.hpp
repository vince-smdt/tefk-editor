#pragma once
#include <algorithm>
#include <iostream>
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
private:
	void PrintContent() override {
		for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(RowSize(), ' ');
		}
	}
public:
	Panel()
		: GUIComponent{}
	{}
};

}