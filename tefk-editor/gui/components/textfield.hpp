#pragma once
#include "base/text.hpp"

namespace tefk {

class TextField : public Text {
    TefkString _label;
    std::function<void()> _onSubmit;
public:
    TextField();

    // Label
    TefkString GetLabel();
    void SetLabel(TefkString label);

    // Formatted string
    TefkString GetFormattedString();

    // Events
    void SetOnSubmit(std::function<void()> func);

    // Overrides
    bool CatchEventFromBaseComponent(Event event) override;
private:
    TefkCoordSizeT GetContentWidth() override;
    TefkCoordSizeT GetContentHeight() override;
    void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk
