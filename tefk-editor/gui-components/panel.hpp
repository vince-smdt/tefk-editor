#pragma once
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

		// Print panel
		for (short currRow = 0; currRow < _size.Y; currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(_size.X, ' ');
		}

		// Print children elements of panel
		for (auto &child : _children) {
			child->Print();
		}
	}
};

}