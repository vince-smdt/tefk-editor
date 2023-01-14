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

	// Position cursor at start of console window
	ss << "\x1b[0;0H";

	// Build output string with canvas
	for (size_t y = 0; y < _size.Y; y++) {
		for (size_t x = 0; x < _size.X; x++) {
			Pixel currPixel = PixelAt(x, y);

			// Switch color if different
			if (currentColor != currPixel.color) {
				currentColor = currPixel.color;
				ss << "\x1b[" << currentColor.Foreground() << ";" << currentColor.Background() << "m";
			}

			// Write character
			ss << currPixel.character;
		}

		// Write newline every row if not at last row
		if (y != _size.Y - 1)
			ss << '\n';
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

} // namespace tefk