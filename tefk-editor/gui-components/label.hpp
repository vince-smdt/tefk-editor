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

		// Row size to print, exclude overflow from console window
		short rowSize = (std::min)(
			_size.X,
			(short)(ConsoleAPI::ColCount() - _pos.X)
		);

		if (rowSize == 0)
			return;

		// Print label
		if (rowSize > 0) {
			for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(rowSize * currRow) < _text.size(); currRow++) {
				ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
				std::cout << _text.substr((int)(currRow * rowSize), rowSize);
			}
		}
	}
};

}