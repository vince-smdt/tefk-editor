#pragma once
#include <vector>

#include "color.hpp"
#include "consoleapi.hpp"

namespace tefk {

struct Pixel {
	TefkChar character;
	TextColor color;

	Pixel()
		: character{ ' ' }
	{}
};

class Canvas {
	std::vector<Pixel> _pixels;
	Coord _dimensions;	
public:
	Canvas();

	void Render();
	Pixel& PixelAt(size_t x, size_t y);
	void Resize(size_t x, size_t y);
};

} // namespace tefk