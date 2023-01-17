#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	std::string _text;
public:
	Label();

	void SetText(std::string text);

	std::string GetContent() override;
private:
	void DrawOnCanvas() override;
};

} // namespace tefk