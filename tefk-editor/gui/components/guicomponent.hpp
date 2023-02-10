#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "../canvas.hpp"
#include "../color.hpp"
#include "../consoleapi.hpp"
#include "../input.hpp"
#include "../types.h"
#include "window.hpp"

namespace tefk {

enum class SizeBehaviour {
	FIXED,
	CONTENT,
	FILL
};

class Window;

class GUIComponent {
protected:
	Window* _parent;
	Coord _pos;
	Coord _size;
	TextColor _color;
	SizeBehaviour _sizeBehaviour;
	bool _visible;
public:
	GUIComponent();

	// Parent
	void SetParent(Window& window);
	Window& GetParent();

	// Position
	void SetPosition(Coord pos);
	Coord GetPosition();
	
	// Width
	void SetWidth(short width);
	short GetWidth();
	
	// Height
	void SetHeight(short height);
	short GetHeight();
	
	// Size behaviour
	void SetSizeBehaviour(SizeBehaviour sizeBehaviour);
	SizeBehaviour GetSizeBehaviour();
	
	// Color
	void SetColor(TextColor color);
	TextColor GetColor();
	
	// Visibility
	void SetVisibility(bool visible);
	bool IsVisible();

	// Focus
	bool Focused();

	// Virtual methods
	virtual TefkString GetContent() = 0;
	virtual void CatchEvent(Event event) {}
	virtual void DrawOnCanvas() = 0;
};

} // namespace tefk