#pragma once
#include <Windows.h>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class Container;

class GUIComponent {
protected:
	COORD _pos;
	COORD _size;
	TextColor _color;
	Container* _parent;
public:
	GUIComponent()
		: _pos{ 0, 0 },
		  _size{ 0, 0 },
		  _color{ BLACK, BLACK }, // TODO - set to default component color?
		  _parent{ nullptr }
	{}

	COORD GetPosition() { return _pos; }
	COORD GetSize() { return _size; }
	TextColor GetColor() { return _color; }
	Container* GetParent() { return _parent; }

	void SetPosition(COORD pos) { _pos = pos; }
	void SetSize(COORD size) { _size = size; }
	void SetColor(TextColor color) { _color = color; }
	void SetParent(Container *component) { _parent = component; }
	
	virtual void Print() {}
};

}
