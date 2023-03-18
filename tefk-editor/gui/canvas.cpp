#include "canvas.hpp"

namespace tefk {

Canvas::Canvas() 
    : _dimensions{ 0, 0 }
{}

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

            // TODO - Make less repetitive
            ss << "\x1b[38;2;" << currentColor.Foreground().Red << ";"
                               << currentColor.Foreground().Green << ";"
                               << currentColor.Foreground().Blue << "m\x1b[48;2;"
                               << currentColor.Background().Red << ";"
                               << currentColor.Background().Green << ";"
                               << currentColor.Background().Blue << "m";
        }

        // Write character
        TefkChar ch = _pixels[i].character;
        switch (ch) {
        case L'%':
            ss << _pixels[i].character << _pixels[i].character;
            break;
        default:
            ss << _pixels[i].character;
            break;
        }
    }

    // Reset color
    ss << "\x1b[0m";

    // Print content to console
    wprintf(ss.str().c_str());
}

Pixel& Canvas::PixelAt(size_t x, size_t y) {
    size_t index = x + y * _dimensions.X;
    assert(0 <= index && index < _pixels.size());
    return _pixels[index];
}

void Canvas::Resize(size_t x, size_t y) {
    size_t size = x * y;
    assert(0 <= size);
    _dimensions = { (TefkCoordSizeT)x, (TefkCoordSizeT)y };
    _pixels.resize(size);
}

} // namespace tefk
