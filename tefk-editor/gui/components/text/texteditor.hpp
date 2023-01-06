#pragma once
#include <list>

#include "text.hpp"

namespace tefk {

class TextEditor : public Text {
	std::vector<std::string> _rows;
public:
	TextEditor();

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

} // namespace tefk