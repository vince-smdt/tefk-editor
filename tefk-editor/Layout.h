#pragma once
#include "WindowData.h"

#include <vector>

namespace tefk {

class Layout
{
public:
    WindowData* CreateWindow(int y, int x, int begy, int begx);
    int RefreshWindows();

    ~Layout();
private:
    std::vector<WindowData*> windows;
};

} // namespace tefk
