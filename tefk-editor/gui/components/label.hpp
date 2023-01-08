#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	std::string _text;
public:
	Label();

	std::string GetText();
	void SetText(std::string text);
private:
	Coord GetTrueSize() override;
	void DrawOnCanvas(Coord size) override;
};

} // namespace tefk