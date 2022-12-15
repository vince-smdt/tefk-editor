#pragma once
#include <iostream>
#include <vector>
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
private:
	std::vector<GUIComponent*> _children;
public:
	Panel(COORD pos, COORD size, TextColor color)
		: GUIComponent{ pos, size, color },
		  _children{}
	{}

	void Print() override {
		ConsoleAPI::SetTextColor(_color);

		// Print panel
		for (SHORT currRow = 0; currRow < _size.Y; currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << std::string(_size.X, ' ');
		}

		// Print children elements of panel
		for (auto &child : _children) {
			child->Print();
		}
	}

	// TODO - prevent circular parent/child connections
	void AddComponent(GUIComponent &component) {
		_children.push_back(&component);
	}
};

}