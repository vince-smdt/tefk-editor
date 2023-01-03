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

	void CatchEvent(Event& event) override;

	// Editor actions
	void AddChar(char ch);
	void NewLine();
	void DeleteChar();
	void DeleteWord();

	void MoveCursorRight();
	void MoveCursorLeft();
	void MoveCursorUp();
	void MoveCursorDown();
private:
	void PrintContent();
	void PrintCursor();
};

}