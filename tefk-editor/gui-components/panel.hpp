#pragma once
#include <algorithm>
#include <iostream>
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
public:
	Panel();
private:
	void PrintContent() override;
};

}