#include "textfield.hpp"

namespace tefk {

TextField::TextField()
	: GUIComponent{}
{}

void TextField::DrawOnCanvas(Coord size) {
	// If input text can't fit in parent component, shorten string
	std::string truncatedText = (_input.size() > size.X * size.Y)
		? _input.substr(_input.size() - (size.X * size.Y))
		: _input;

	// Print label
	for (short currRow = 0; currRow < size.Y && currRow + _pos.Y < ConsoleAPI::RowCount() && int(size.X * currRow) < truncatedText.size(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = truncatedText.substr(int(currRow * size.X), size.X);
		std::cout.write(row.c_str(), row.size());
	}
}

} // namespace tefk