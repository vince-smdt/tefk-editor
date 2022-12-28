#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include "../color.hpp"
#include "../consoleapi.hpp"

namespace tefk {

class GUIComponent : public std::enable_shared_from_this<GUIComponent> {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;

	std::function<Coord(void)> _dynamicPositionSetter;
	std::function<short(void)> _dynamicHeightSetter;
public:
	GUIComponent();
	GUIComponent(Coord pos, Coord size, TextColor color);

	void SetPosition(Coord pos);
	void SetHeight(short height);
	void SetColor(TextColor color);

	void SetDynamicPosition(std::function<Coord(void)> func);
	void SetDynamicHeight(std::function<short(void)> func);

	void Print();
protected:
	// Size of row that can be printed, excludes overflow
	short RowSize();

	// TODO - Find better name
	virtual void PrintContent() = 0;
};

}
