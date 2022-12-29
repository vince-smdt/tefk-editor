#pragma once
#include "guicomponent.hpp"

namespace tefk {

class TextEditor : public GUIComponent {
	std::string _text;
public:
	TextEditor();
	TextEditor(Coord pos, Coord size, TextColor color);
	void SetText(std::string text);
private:
	void PrintContent();
};

}