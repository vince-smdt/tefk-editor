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

		// Row size to print, exclude overflow from console window
		short rowSize = (std::min)(
			_size.X,
			(short)(ConsoleAPI::ColCount() - _pos.X)
		);

		if (rowSize == 0)
			return;

		// If input text can't fit in parent component, shorten string
		std::string truncatedText = (_input.size() > _size.X * _size.Y)
			? _input.substr(_input.size() - (_size.X * _size.Y))
			: _input;

		// Print label
		for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(rowSize * currRow) < truncatedText.size(); currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << truncatedText.substr((int)(currRow * rowSize), rowSize);
		}
	}
};

}