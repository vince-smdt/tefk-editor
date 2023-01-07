#pragma once
#include "../guicomponent.hpp"

namespace tefk {

class TextField : public GUIComponent {
	std::string _input;
public:
	TextField();
private:
	void DrawOnCanvas() override;
};

} // namespace tefk