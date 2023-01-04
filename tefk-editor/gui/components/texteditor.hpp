#pragma once
#include <list>
#include "guicomponent.hpp"

namespace tefk {

struct Cursor {
	std::vector<std::string>::iterator row;
	std::string::iterator col;
};

class TextEditor : public GUIComponent {
	std::vector<std::string> _rows;
	Cursor _cursor;
public:
	TextEditor();
	TextEditor(Coord pos, Coord size, TextColor color);

	void SetText(std::string text);
	std::string GetText();

	void CatchEvent(Event& event) override;

	// Editor actions
	void AddChar(unsigned char ch);
	void NewLine();
	void DeleteChar();
	void DeleteWord();

	void MoveCursorRight();
	void MoveCursorLeft();
	void MoveCursorUp();
	void MoveCursorDown();

	void MoveCursorNextWord();
	void MoveCursorPrevWord();
private:
	void PrintContent();
	void PrintCursor();
};

}