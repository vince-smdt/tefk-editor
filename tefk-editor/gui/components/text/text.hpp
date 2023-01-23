#include "../guicomponent.hpp"

namespace tefk {

struct Cursor {
	std::vector<std::string>::iterator row;
	std::string::iterator col;
};

class Text : public GUIComponent {
protected:
	Cursor _cursor;
	std::vector<std::string> _rows;
public:
	Text();

	Coord GetCursorPos();

	// Text commands
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
};

} // namespace tefk