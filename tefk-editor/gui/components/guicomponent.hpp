#pragma once
#include <algorithm>
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
	GUIComponent(Coord pos, Coord size, TextColor color);

	void SetPosition(Coord pos);
	void SetHeight(short height);
	void SetColor(TextColor color);

	void Print();
protected:
	// Size of row that can be printed, excludes overflow
	short RowSize();

	// TODO - Find better name
	virtual void PrintContent() = 0;
};

}
