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

	void Render();
	virtual void CatchEvent(Event& event) {}
protected:
	virtual Coord GetTrueSize();
	virtual short GetTrueSizeAxis(short length, short containerLength, short position);
	virtual void DrawOnCanvas(Coord size) = 0;
};

} // namespace tefk