#pragma once
#include <vector>

#include "color.hpp"
#include "consoleapi.hpp"

namespace tefk {

class Canvas {
	struct Pixel {
		char character;
		TextColor color;
	};

	std::vector<Pixel> _pixels;
	Coord _size;
	
	Canvas();
public:
	static Canvas& Instance();

	void Render();
	Pixel& PixelAt(size_t x, size_t y);
	void Resize(size_t x, size_t y);
};

} // namespace tefk