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

		// Get position relative to parent, else origin
		Coord relPos = (_parent) 
			? _parent->GetPosition() 
			: _ORIGIN;

		// Calculate real/current position
		Coord currPos = { _pos.X + relPos.X, _pos.Y + relPos.Y };

		// Row size to print, exclude overflow from console window
		short rowSize = (std::min)(
			_size.X, 
			(short)(ConsoleAPI::ColCount() - _pos.X)
		);

		// Print panel
		// TODO - hide children element overflow
		if (rowSize > 0) {
			for (short currRow = 0; currRow < _size.Y && currRow + currPos.Y < ConsoleAPI::RowCount(); currRow++) {
				ConsoleAPI::SetCursorPos(currPos.Y + currRow, currPos.X);
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