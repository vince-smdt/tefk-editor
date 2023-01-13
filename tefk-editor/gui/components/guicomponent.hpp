#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../canvas.hpp"
#include "../color.hpp"
#include "../consoleapi.hpp"
#include "../input.hpp"

namespace tefk {

enum class SizeBehaviour {
	FIXED,
	CONTENT,
	FILL
};

class GUIComponent {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	SizeBehaviour _heightBehaviour;
	bool _visible;
public:
	GUIComponent(SizeBehaviour heightBehaviour);

	void SetPosition(Coord pos);
	void SetWidth(short width);
	void SetHeight(short height);
	void SetColor(TextColor color);
	void SetVisible(bool visible);

	short GetHeight();
	SizeBehaviour GetHeightBehaviour();
	bool IsVisible();

	virtual short UpdateHeight() { return 0; }; // TODO - maybe make it so we don't have to return a value
	virtual void CatchEvent(Event& event) {}
	virtual void DrawOnCanvas() = 0;
};

} // namespace tefk