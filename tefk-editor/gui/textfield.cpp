#include "textfield.hpp"

namespace tefk {

TextField::TextField()
	: GUIComponent{}
{}

void TextField::AddText(std::string text) {
	_input += text;
}

void TextField::PrintContent() {
	// If input text can't fit in parent component, shorten string
	std::string truncatedText = (_input.size() > _size.X * _size.Y)
		? _input.substr(_input.size() - (_size.X * _size.Y))
		: _input;

	// Print label
	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(RowSize() * currRow) < truncatedText.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::cout << truncatedText.substr((int)(currRow * RowSize()), RowSize());
	}
}

}