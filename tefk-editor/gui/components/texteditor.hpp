#pragma once
#include <list>

#include "base/text.hpp"

namespace tefk {

class TextEditor : public Text {
public:
    TextEditor();

    // Text
    void SetText(TefkString text);

    // Actions
    void Tab();

    // Overrides
    bool CatchEventFromBaseComponent(Event event) override;
private:
    TefkCoordSizeT GetContentWidth() override;
    TefkCoordSizeT GetContentHeight() override;
    void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk
