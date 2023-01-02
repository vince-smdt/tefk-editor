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
	std::string GetText();

	void AddChar(char ch);
	void NewLine();
	void DeleteChar();
	void DeleteWord();
private:
	void PrintContent();
	void PrintCursor();
};

}