#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>

#include "../../canvas.hpp"
#include "../../color.hpp"
#include "../../consoleapi.hpp"
#include "../../input.hpp"
#include "../../types.h"
#include "../../window.hpp"

namespace tefk {

enum class SizeBehaviour {
    FIXED,
    CONTENT,
    FILL
};

// Forward declarations
class Window;

class GUIComponent {
protected:
    Window* _parent;
    TefkCoord _pos;
    TefkCoord _size;
    TextColor _color;
    SizeBehaviour _sizeBehaviour;
    bool _visible;
public:
    GUIComponent();

    // Parent
    void SetParent(Window& window);
    Window& GetParent();

    // Position
    void SetPosition(TefkCoord pos);
    TefkCoord GetPosition();
    
    // Width
    void SetWidth(TefkCoordSizeT width);
    TefkCoordSizeT GetWidth();
    
    // Height
    void SetHeight(TefkCoordSizeT height);
    TefkCoordSizeT GetHeight();
    
    // Size behaviour
    void SetSizeBehaviour(SizeBehaviour sizeBehaviour);
    SizeBehaviour GetSizeBehaviour();
    
    // Color
    void SetColor(TextColor color);
    TextColor GetColor();
    
    // Visibility
    void SetVisibility(bool visible);
    bool IsVisible();

    // Focus
    bool Focused();

    // Canvas
    Canvas& GetCanvas();
    void DrawOnCanvas();

    // Virtual methods
    virtual TefkString GetContent() = 0;
    virtual void CatchEvent(Event event) {}
    virtual void GetPixelVector(PixelVector& pixelVec) = 0;
};

} // namespace tefk
