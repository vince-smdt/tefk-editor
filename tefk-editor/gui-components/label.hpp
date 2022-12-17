#pragma once
#include <string>
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
private:
	std::string _text;
public:
	Label()
		: GUIComponent{}
	{}

	std::string GetText() { return _text; }

	void SetText(std::string text) { _text = text; }

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
			(short)(ConsoleAPI::ColCount() - currPos.X)
		);

		// Print label
		if (rowSize > 0) {
			for (short currRow = 0; currRow < _size.Y && currRow + currPos.Y < ConsoleAPI::RowCount() && (int)(rowSize * currRow) < _text.size(); currRow++) {
				ConsoleAPI::SetCursorPos(currPos.Y + currRow, currPos.X);
				std::cout << _text.substr((int)(currRow * rowSize), rowSize);
			}
		}

		// Print children elements of label
		for (auto& child : _children) {
			child->Print();
		}
	}
};

}