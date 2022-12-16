#pragma once
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class Container;

class GUIComponent {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	Container* _parent;
public:
	GUIComponent()
		: _pos{ 0, 0 },
		  _size{ 0, 0 },
		  _color{ BLACK, BLACK }, // TODO - set to default component color?
		  _parent{ nullptr }
	{}

	Coord GetPosition() { return _pos; }
	Coord GetSize() { return _size; }
	TextColor GetColor() { return _color; }
	Container* GetParent() { return _parent; }

	void SetPosition(Coord pos) { _pos = pos; }
	void SetSize(Coord size) { _size = size; }
	void SetColor(TextColor color) { _color = color; }
	void SetParent(Container *component) { _parent = component; }
	
	virtual void Print() {}
};

}
