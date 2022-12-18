#pragma once
#include <memory>
#include <vector>
#include "color.h"
#include "consoleapi.hpp"

namespace tefk {

class GUIComponent : public std::enable_shared_from_this<GUIComponent> {
protected:
	Coord _pos;
	Coord _size;
	TextColor _color;
	std::shared_ptr<GUIComponent> _parent;
	std::vector<std::shared_ptr<GUIComponent>> _children;
	
	const Coord _ORIGIN = { 0, 0 };
public:
	GUIComponent()
		: _pos{ _ORIGIN },
		  _size{ _ORIGIN },
		  _color{ BLACK, BLACK }, // TODO - set to default component color?
		  _parent{ nullptr }
	{}

	Coord GetPosition() { return _pos; }
	Coord GetSize() { return _size; }
	TextColor GetColor() { return _color; }
	std::shared_ptr<GUIComponent> GetParent() { return _parent; }

	void SetPosition(Coord pos) { _pos = pos; }
	void SetSize(Coord size) { _size = size; }
	void SetColor(TextColor color) { _color = color; }
	void SetParent(std::shared_ptr<GUIComponent> component) { _parent = component; }

	// TODO - prevent circular parent/child connections
	void AddComponent(std::shared_ptr<GUIComponent> component) {
		component->SetParent(shared_from_this());
		_children.push_back(std::move(component));
	}
	
	virtual void Print() {}
};

}
