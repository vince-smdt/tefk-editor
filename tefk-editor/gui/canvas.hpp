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

    Pixel(TefkChar ch, TextColor color)
        : character{ ch }
        , color{ color }
    {}
};

using PixelVector = std::vector<Pixel>;

class Canvas {
    PixelVector _pixels;
    TefkCoord _dimensions;
public:
    Canvas();

    void Render();
    Pixel& PixelAt(TefkCoordSizeT x, TefkCoordSizeT y);
    void Resize(TefkCoordSizeT x, TefkCoordSizeT y);
};

} // namespace tefk
