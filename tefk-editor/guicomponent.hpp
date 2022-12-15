#pragma once
#include <Windows.h>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class GUIComponent {
protected:
	COORD _pos;
	COORD _size;
	TextColor _color;
	GUIComponent* _parent;
public:
	GUIComponent(COORD pos, COORD size, TextColor color)
		: _pos{ pos },
		_size{ size },
		_color{ color },
		_parent{ nullptr }
	{}

	virtual void Print() {}
};

}