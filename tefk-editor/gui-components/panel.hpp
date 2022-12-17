#pragma once
#include <algorithm>
#include <iostream>
#include "gui-components/container.hpp"

namespace tefk {

class Panel : public GUIComponent, public Container {
public:
	Panel()
		: GUIComponent{},
		  Container{}
	{}

	void Print() override {
		ConsoleAPI::SetTextColor(_color);

		// Row size to print, exclude overflow from console window
		short rowSize = (std::min)(
			_size.X, 
			(short)(ConsoleAPI::ColCount() - _pos.X)
		);

		// Print panel
		if (rowSize > 0) {
			for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
				ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
				std::cout << std::string(rowSize, ' ');
			}
		}

		// Print children elements of panel
		for (auto &child : _children) {
			child->Print();
		}
	}
};

}