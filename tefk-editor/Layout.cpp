#include "Layout.h"
#include "Logger.h"
#include "CastMacros.h"
#include "CursesMacros.h"

#include <curses.h>

namespace tefk {

WindowData* Layout::CreateWindow(int y, int x, int begy, int begx)
{
    TEFK_LOG_TRACE("Layout::CreateWindow({}, {}, {}, {}, {})", V_PTR(this), y, x, begy, begx);

    WindowData *windata = new WindowData;
    windata->win = newwin(y, x, begy, begx);
    windata->layout = this;
    windows.push_back(windata);

    TEFK_LOG_TRACE("Layout::ExitCreateWindow({})", V_PTR(this));
    return windata;
}

int Layout::RefreshWindows()
{
    TEFK_LOG_TRACE("Layout::RefreshWindows({})", V_PTR(this));

    for (WindowData *windata : windows)
        RET_IF_ERR(wrefresh(windata->win));

    TEFK_LOG_TRACE("Layout::ExitRefreshWindows({})", V_PTR(this));
    return OK;
}

Layout::~Layout()
{
    TEFK_LOG_TRACE("Layout::~Layout({})", V_PTR(this));

    for (WindowData *windata : windows)
    {
         delwin(windata->win);
         delete windata;
    }

    TEFK_LOG_TRACE("Layout::Exit~Layout({})", V_PTR(this));
}

} // namespace tefk
