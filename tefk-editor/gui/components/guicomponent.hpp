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

	short GetWidth();
	short GetHeight();
	SizeBehaviour GetHeightBehaviour();
	bool IsVisible();

	virtual std::string GetContent() = 0;
	virtual void CatchEvent(Event& event) {}

	void Draw();
protected:
	virtual void DrawPixel(short x, short y) = 0;
};

} // namespace tefk