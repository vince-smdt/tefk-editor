#pragma once
#include "CursesTypes.h"

namespace tefk {

// Forward declarations
class Layout;

struct WindowData
{
    Window *win;
    Layout *layout; // TODO - Find use for this or delete
};

} // namespace tefk
