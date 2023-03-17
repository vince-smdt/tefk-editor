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

    // Events
    void SetOnSubmit(std::function<void()> func);

    // Overrides
    TefkString GetContent() override;
    bool CatchEventFromBaseComponent(Event event) override;
private:
    void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk
