#pragma once
#include "base/guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
    TefkString _text;
public:
    Label();

    // Text
    void SetText(TefkString text);
private:
    TefkCoordSizeT GetContentWidth() override;
    TefkCoordSizeT GetContentHeight() override;
    void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk
