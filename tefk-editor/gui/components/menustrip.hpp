#pragma once
#include "base/guicomponent.hpp"

namespace tefk {

class MenuStrip : public GUIComponent {
public:
    MenuStrip();
private:
    TefkCoordSizeT GetContentWidth() override;
    TefkCoordSizeT GetContentHeight() override;
    void GetPixelVector(PixelVector& pixelVec) override;
};

}
