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

Coord Label::GetTrueSize() {
	Coord size;
	size.X = GetTrueSizeAxis(_size.X, ConsoleAPI::ColCount(), _pos.X);
	size.Y = (short)ceil(double(_text.size()) / _size.X);
	return size;
}

void Label::DrawOnCanvas(Coord size) {
	// Print text
	for (short currRow = 0; currRow < size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && int(size.X * currRow) < _text.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = _text.substr(int(currRow * size.X), size.X);
		std::cout.write(row.c_str(), row.size());
	}

	// Print filling white space
	size_t lastRowSize = _text.size() % size.X;
	std::cout.write(std::string(size.X - lastRowSize, ' ').c_str(), size.X - lastRowSize);
}

} // namespace tefk