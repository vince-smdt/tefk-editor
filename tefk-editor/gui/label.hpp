#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	std::string _text;
	std::function<std::string(void)> _dynamicTextSetter;
public:
	Label();

	std::string GetText();
	void SetText(std::string text);
	void SetDynamicText(std::function<std::string(void)> func);
private:
	void PrintContent() override;
};

}