#pragma once
#include "base/guicomponent.hpp"

namespace tefk {

class MenuStrip : public GUIComponent {
public:
    MenuStrip();

    TefkString GetContent() override;
private:
    void GetPixelVector(PixelVector& pixelVec) override;
};

}
