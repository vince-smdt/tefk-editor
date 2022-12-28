#include "panel.hpp"

namespace tefk {

Panel::Panel()
	: GUIComponent{}
{}

Panel::Panel(Coord pos, Coord size, TextColor color)
	: GUIComponent{ pos, size, color }
{}

void Panel::PrintContent() {
	for (short currRow = 0; currRow < _size.Y && currRow + _pos.Y < ConsoleAPI::RowCount(); currRow++) {
		ConsoleAPI::SetCursorPos(_pos.Y + currRow, _pos.X);
		std::string row = std::string(RowSize(), ' ');
		std::cout.write(row.c_str(), row.size());
	}
}

}