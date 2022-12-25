#pragma once
#include "guicomponent.hpp"

namespace tefk {

class TextField : public GUIComponent {
	std::string _input;
public:
	TextField();

	void AddText(std::string text);
private:
	void PrintContent();
};

}