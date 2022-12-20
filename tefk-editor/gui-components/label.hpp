#pragma once
#include <string>
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
private:
	std::string _text;

	void PrintContent() override {
		for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(RowSize() * currRow) < _text.size(); currRow++) {
			ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
			std::cout << _text.substr((int)(currRow * RowSize()), RowSize());
		}
	}
public:
	Label()
		: GUIComponent{}
	{}

	std::string GetText() { 
		return _text; 
	}

	void SetText(std::string text) { 
		_text = text; 
	}
};

}