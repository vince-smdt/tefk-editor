#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../color.hpp"
#include "../consoleapi.hpp"
#include "../input.hpp"

namespace tefk {

enum class SizeBehaviour {
	AUTO,
	CONTENT,
	FILL
};

class GUIComponent {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	SizeBehaviour _heightBehaviour;
public:
	GUIComponent(SizeBehaviour heightBehaviour);

	void SetPosition(Coord pos); // TODO - remove this function, replace with responsive system
	void SetHeight(short height);
	void SetColor(TextColor color);

	short GetHeight();
	SizeBehaviour GetHeightBehaviour();

	void Render();
	virtual short UpdateHeight() { return 0; }; // TODO - maybe make it so we don't have to return a value
	virtual void CatchEvent(Event& event) {}
protected:
	virtual void DrawOnCanvas() = 0;
};

} // namespace tefk