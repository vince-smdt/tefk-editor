#include "label.hpp"

namespace tefk {

Label::Label()
	: GUIComponent{ SizeBehaviour::CONTENT }
{}

std::string Label::GetText() {
	return _text;
}

void Label::SetText(std::string text) {
	_text = text;
}

short Label::UpdateHeight() {
	short divider = _size.X == 0 ? _text.size() : _size.X;
	return _size.Y = (short)ceil(double(_text.size()) / divider);
}

void Label::DrawOnCanvas() {
	// Print text
	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && int(_size.X * currRow) < _text.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = _text.substr(int(currRow * _size.X), _size.X);
		std::cout.write(row.c_str(), row.size());
	}

	// Print filling white space
	size_t lastRowSize = _text.size() % _size.X;
	std::cout.write(std::string(_size.X - lastRowSize, ' ').c_str(), _size.X - lastRowSize);

	for (size_t y = _pos.Y; y < _size.Y + _pos.Y; y++) {
		for (size_t x = _pos.X; x < _size.X + _pos.X; x++) {
			size_t charIndex = x + y * _size.Y;

			Canvas::Instance().PixelAt(x, y).character = charIndex >= _text.size() ? ' ' : _text[charIndex];
			Canvas::Instance().PixelAt(x, y).color = _color;
		}
	}
}

} // namespace tefk