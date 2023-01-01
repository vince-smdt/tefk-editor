#pragma once
#include <list>
#include "guicomponent.hpp"

namespace tefk {

class TextEditor : public GUIComponent {
	std::vector<std::string> _rows;
	std::vector<std::string>::iterator _cursorRow;
	std::string::iterator _cursorCol;
public:
	TextEditor();
	TextEditor(Coord pos, Coord size, TextColor color);
	void SetText(std::string text);
private:
	void PrintContent();
};

}