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
    TefkString GetContent() override;
    bool CatchEventFromBaseComponent(Event event) override;
private:
    void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk
