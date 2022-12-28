#pragma once
#include "guicomponent.hpp"

namespace tefk {

class TextField : public GUIComponent {
	std::string _input;
public:
	TextField();
	TextField(Coord pos, Coord size, TextColor color);
private:
	void PrintContent();
};

}