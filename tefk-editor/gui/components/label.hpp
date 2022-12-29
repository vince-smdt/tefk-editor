#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	std::string _text;
public:
	Label();
	Label(Coord pos, Coord size, TextColor color);

	std::string GetText();
	void SetText(std::string text);
private:
	void PrintContent() override;
};

}