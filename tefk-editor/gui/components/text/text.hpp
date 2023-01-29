#pragma once
#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
protected:
	std::list<unsigned char> _text;
	std::list<unsigned char>::iterator _cursor;
public:
	Text(SizeBehaviour heightBehaviour);

	// Setters & Getters
	std::string GetText();

	// Commands
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

	// Events
	void CatchEvent(Event event) override;
	virtual bool CatchEventFromBaseComponent(Event event) { return false; }
protected:
	// Helper functions
	size_t SpacesFromLeft();
};

} // namespace tefk