#include "label.hpp"

namespace tefk {

Label::Label()
	: GUIComponent{}
{}

std::string Label::GetText() {
	return _text;
}

void Label::SetText(std::string text) {
	_text = text;
}

void Label::PrintContent() {
	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && (int)(RowSize() * currRow) < _text.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::cout << _text.substr((int)(currRow * RowSize()), RowSize());
	}
}

}