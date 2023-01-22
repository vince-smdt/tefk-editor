#pragma once
#include "../guicomponent.hpp"

namespace tefk {

class TextField : public GUIComponent {
	std::string _label;
	std::string _input;
public:
	TextField();

	std::string GetLabel();
	void SetLabel(std::string label);

	std::string GetContent() override;
private:
	void DrawPixel(Coord pos, Pixel* pixel) override;
};

} // namespace tefk