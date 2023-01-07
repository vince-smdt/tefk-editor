#include "canvas.hpp"

namespace tefk {

Canvas::Canvas() 
	: _size{ 0, 0 }
{}

void Canvas::Render(Window& window) {
	window.Render();
}

Canvas::Pixel& Canvas::PixelAt(size_t x, size_t y) {
	// TODO - check if target pixel is out of vector range
	return _pixels[x + y * _size.Y];
}

void Canvas::Resize(size_t x, size_t y) {
	// TODO - check if both x and y are positive
	_pixels.resize(x + y * _size.Y);
}

} // namespace tefk