#pragma once
#include "CursesTypes.h"

namespace tefk {

class Application {
public:
    int Initialize();
    int Run();
    int Finalize();

    int ResizeWindow(Window *&win, int y, int x); // TODO - Move this elsewhere
    int ReconfigWindow(Window *&win, int y, int x, int begy, int begx); // TODO - Move this elsewhere
};

} // namespace tefk
