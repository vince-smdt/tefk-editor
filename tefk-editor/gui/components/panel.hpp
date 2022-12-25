#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Panel : public GUIComponent {
public:
	Panel();
private:
	void PrintContent() override;
};

}