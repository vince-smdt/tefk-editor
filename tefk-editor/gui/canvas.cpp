#include "canvas.hpp"

namespace tefk {

Canvas::Canvas() 
	: _size{ 0, 0 }
{}

Canvas& Canvas::Instance() {
	static Canvas instance;
	return instance;
}

void Canvas::Render() {

}

Canvas::Pixel& Canvas::PixelAt(size_t x, size_t y) {
	// TODO - check if target pixel is out of vector range
	return _pixels[x + y * _size.Y];
}

void Canvas::Resize(size_t x, size_t y) {
	// TODO - check if both x and y are positive
	_size = { (short)x, (short)y };
	_pixels.resize(x * y);
}

} // namespace tefk