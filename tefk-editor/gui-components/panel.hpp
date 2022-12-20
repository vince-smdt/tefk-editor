#pragma once
#include <algorithm>
#include <iostream>
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
public:
	Panel()
		: GUIComponent{}
	{}

	void Print() override {
		ConsoleAPI::SetTextColor(_color);

		// Row size to print, exclude overflow from console window
		short rowSize = (std::min)(
			_size.X, 
			(short)(ConsoleAPI::ColCount() - _pos.X)
		);

		if (rowSize == 0)
			return;

		// Print panel
		for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(rowSize, ' ');
		}
	}
};

}