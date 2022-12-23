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

	std::function<Coord(void)> _dynamicPositionSetter;
	std::function<Coord(void)> _dynamicSizeSetter;
	std::function<TextColor(void)> _dynamicColorSetter;
	
	const Coord _ORIGIN = { 0, 0 };
public:
	GUIComponent();

	Coord GetPosition();
	Coord GetSize();
	TextColor GetColor();

	void SetPosition(Coord pos);
	void SetSize(Coord size);
	void SetColor(TextColor color);

	void SetDynamicPosition(std::function<Coord(void)> func);
	void SetDynamicSize(std::function<Coord(void)> func);
	void SetDynamicColor(std::function<TextColor(void)> func);

	void Print();
protected:
	// Row size that can be printed, excludes overflow
	short RowSize();

	// TODO - Find better name
	virtual void PrintContent() = 0;
};

}
