#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
public:
	Panel();
	Panel(Coord pos, Coord size, TextColor color);
private:
	void PrintContent() override;
};

}