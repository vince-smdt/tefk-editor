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
	std::wstringstream ss;
	TextColor currentColor;

	// Hide cursor
	ss << "\x1b[?25l";

	// Position cursor at start of console window
	ss << "\x1b[0;0H";

	// Build output string with canvas
	for (size_t i = 0; i < _pixels.size(); i++) {
		// Switch color if different
		if (currentColor != _pixels[i].color) {
			currentColor = _pixels[i].color;
			ss << "\x1b[" << currentColor.Foreground() << ";" << currentColor.Background() << "m";
		}

		// Write character
		ss << _pixels[i].character;
	}

	// Reset color
	ss << "\x1b[0m";

	// Print content to console
	wprintf(ss.str().c_str());
}

Pixel& Canvas::PixelAt(size_t x, size_t y) {
	// TODO - check if target pixel is out of vector range
	return _pixels[x + y * _size.X];
}

void Canvas::Resize(size_t x, size_t y) {
	// TODO - check if both x and y are positive
	_size = { (short)x, (short)y };
	_pixels.resize(x * y);
}

Canvas& GetCanvas() {
	return Canvas::Instance();
}

} // namespace tefk