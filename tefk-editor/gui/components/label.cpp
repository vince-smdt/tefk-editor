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

void Label::DrawOnCanvas() {
	short height = (short) ceil(double(_text.size()) / RowSize());

	// Print text
	for (short currRow = 0; currRow < height && currRow + _pos.Y < ConsoleAPI::RowCount() && int(RowSize() * currRow) < _text.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = _text.substr(int(currRow * RowSize()), RowSize());
		std::cout.write(row.c_str(), row.size());
	}

	// Print filling white space
	size_t lastRowSize = _text.size() % RowSize();
	std::cout.write(std::string(RowSize() - lastRowSize, ' ').c_str(), RowSize() - lastRowSize);
}

} // namespace tefk