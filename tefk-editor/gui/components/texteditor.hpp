#pragma once
#include "guicomponent.hpp"

namespace tefk {

class TextEditor : public GUIComponent {
	std::string _text;
	std::function<std::string(void)> _dynamicTextSetter; // TODO - remove this when not using SetDynamicText anymore
public:
	TextEditor();
	void SetDynamicText(std::function<std::string(void)> func); // TODO - replace this later
private:
	void PrintContent();
};

}