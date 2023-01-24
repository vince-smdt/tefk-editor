#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
protected:
	std::list<unsigned char> _text;
	std::list<unsigned char>::iterator _cursor;
public:
	Text();

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
protected:
	// Helper functions
	size_t SpacesFromLeft();
};

} // namespace tefk