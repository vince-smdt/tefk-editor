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

	short UpdateHeight() override;
private:
	void DrawOnCanvas() override;
};

} // namespace tefk