#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include "../color.h"
#include "../consoleapi.hpp"

namespace tefk {

class GUIComponent : public std::enable_shared_from_this<GUIComponent> {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	
	const Coord _ORIGIN = { 0, 0 };
public:
	GUIComponent();

	Coord GetPosition();
	Coord GetSize();
	TextColor GetColor();

	void SetPosition(Coord pos);
	void SetSize(Coord size);
	void SetColor(TextColor color);

	void Print();
protected:
	// Row size that can be printed, excludes overflow
	short RowSize();

	// TODO - Find better name
	virtual void PrintContent() = 0;
};

}
