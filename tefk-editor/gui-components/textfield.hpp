#pragma once
#include <string>
#include "guicomponent.hpp"

namespace tefk {

class TextField : public GUIComponent {
private:
	std::string _input;
public:
	TextField()
		: GUIComponent{}
	{}

	void AddText(std::string text) {
		_input += text;
	}

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
			// If input text can't fit in parent component, shorten string
			std::string truncatedText = (_input.size() > _size.X * _size.Y)
				? _input.substr(_input.size() - (_size.X * _size.Y))
				: _input;

			for (short currRow = 0; currRow < _size.Y && currRow + currPos.Y < ConsoleAPI::RowCount() && (int)(rowSize * currRow) < truncatedText.size(); currRow++) {
				ConsoleAPI::SetCursorPos(currPos.Y + currRow, currPos.X);
				std::cout << truncatedText.substr((int)(currRow * rowSize), rowSize);
			}
		}

		// Print children elements of label
		for (auto& child : _children) {
			child->Print();
		}
	}
};

}