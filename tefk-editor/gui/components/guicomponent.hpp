#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../color.hpp"
#include "../consoleapi.hpp"
#include "../input.hpp"

namespace tefk {

class GUIComponent {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
public:
	GUIComponent();

	void SetPosition(Coord pos);
	void SetHeight(short height);
	void SetColor(TextColor color);

	void Print();
	virtual void CatchEvent(Event& event) {}
protected:
	// Size of row that can be printed, excludes overflow
	short RowSize();

	virtual void PrintContent() = 0; // TODO - Find better name
};

} // namespace tefk