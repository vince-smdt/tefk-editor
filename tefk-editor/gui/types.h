#pragma once
#include <string>

namespace tefk {

using TefkString = std::string;
using TefkChar = TefkString::value_type;
using TefkSizeT = TefkString::size_type;

using TefkCoordSizeT = short;
struct TefkCoord {
    TefkCoordSizeT X;
    TefkCoordSizeT Y;

    TefkCoordSizeT Area() {
        return X * Y;
    }

    bool operator==(const TefkCoord& c) {
        return X == c.X && Y == c.Y;
    }

    bool operator!=(const TefkCoord& c) {
        return X != c.X || Y != c.Y;
    }
};

} // namespace tefk
