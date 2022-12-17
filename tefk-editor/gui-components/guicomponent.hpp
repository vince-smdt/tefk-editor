#pragma once
#include <vector>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {


class GUIComponent {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	GUIComponent* _parent;
	std::vector<GUIComponent*> _children;
	
	const Coord _ORIGIN = { 0, 0 };
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
	GUIComponent* GetParent() { return _parent; }

	void SetPosition(Coord pos) { _pos = pos; }
	void SetSize(Coord size) { _size = size; }
	void SetColor(TextColor color) { _color = color; }
	void SetParent(GUIComponent *component) { _parent = component; }

	// TODO - prevent circular parent/child connections
	void AddComponent(GUIComponent& component) {
		_children.push_back(&component);
		component.SetParent(this);
	}
	
	virtual void Print() {}
};

}
