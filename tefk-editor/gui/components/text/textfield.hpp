#pragma once
#include "text.hpp"

namespace tefk {

class TextField : public Text {
	std::string _label;
public:
	TextField();

	std::string GetLabel();
	void SetLabel(std::string label);

	std::string GetContent() override;
private:
	void DrawOnCanvas() override;
};

} // namespace tefk