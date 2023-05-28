#include "Application.h"
#include "CastMacros.h"
#include "CursesMacros.h"
#include "Layout.h"
#include "Logger.h"
#include "TextEditor.h"

#include <curses.h>

namespace tefk {

int Application::Initialize()
{
    TEFK_LOG_TRACE("Application::Initialize({})", V_PTR(this));

    RET_IF_NIL(initscr());
    RET_IF_ERR(noecho());
    RET_IF_ERR(raw());
    RET_IF_ERR(keypad(stdscr, TRUE));
    RET_IF_ERR(nodelay(stdscr, TRUE));
    RET_IF_ERR(curs_set(0));
    RET_IF_ERR(start_color());

    RET_IF_ERR(init_pair(1, COLOR_BLACK, COLOR_WHITE));
    RET_IF_ERR(init_pair(2, COLOR_WHITE, COLOR_BLACK));

    TEFK_LOG_TRACE("Application::ExitInitialize({})", V_PTR(this));
    return OK;
}

int Application::Run()
{
    TEFK_LOG_TRACE("Application::Run({})", V_PTR(this));

    Layout layout;
    WindowData *wHea,
               *wEdi,
               *wFoo;
    TextEditor editor;

    RET_IF_NIL(wHea = layout.CreateWindow(1, 0, 0, 0));
    RET_IF_NIL(wEdi = layout.CreateWindow(getmaxy(stdscr) - 2, 0, 1, 0));
    RET_IF_NIL(wFoo = layout.CreateWindow(1, 0, getmaxy(stdscr) - 1, 0));

    RET_IF_ERR(wbkgd(wHea->win, COLOR_PAIR(1)));
    RET_IF_ERR(wbkgd(wEdi->win, COLOR_PAIR(2)));
    RET_IF_ERR(wbkgd(wFoo->win, COLOR_PAIR(1)));
    RET_IF_ERR(refresh());
    RET_IF_ERR(layout.RefreshWindows());

    char input;
    while ((input = getch()) != 'q')
    {
        if (is_termresized())
        {
            if (resize_term(0, 0) != ERR)
            {
                RET_IF_ERR(ResizeWindow(wHea->win, 1, 0));
                RET_IF_ERR(ResizeWindow(wEdi->win, getmaxy(stdscr) - 2, 0));
                RET_IF_ERR(ReconfigWindow(wFoo->win, 1, 0, getmaxy(stdscr) - 1, 0));
                RET_IF_ERR(layout.RefreshWindows());
            }
        }
        else if (input != ERR)
        {
            switch (input)
            {
                case '\r':    editor.NewLine();       break; // ENTER/RETURN
                case '\b':    editor.DeleteChar();    break; // BACKSPACE
                case 127:     editor.DeleteWord();    break; // CTRL + BACKSPACE
                case '\f':    editor.DeleteLine();    break; // CTRL + L
                case '\x19':  editor.Redo();          break; // CTRL + Y
                case '\x1a':  editor.Undo();          break; // CTRL + Z
                default:      editor.AddChar(input);  break; // ALL OTHER INPUTS
            }
        }

        wclear(wEdi->win);

        std::vector<ChType> text = editor.GetText();
        char *ctext = new char[text.size() + 1];
        for (size_t i = 0; i < text.size(); i++)
            ctext[i] = text[i];
        ctext[text.size()] = '\0';

        mvwaddstr(wEdi->win, 0, 0, ctext);
        delete[] ctext;

        RET_IF_ERR(layout.RefreshWindows());
    }

    TEFK_LOG_TRACE("Application::ExitRun({})", V_PTR(this));
    return OK;
}

int Application::Finalize()
{
    TEFK_LOG_TRACE("Application::Finalize({})", V_PTR(this));

    RET_IF_ERR(endwin());

    TEFK_LOG_TRACE("Application::ExitFinalize({})", V_PTR(this));
    return OK;
}

int Application::ResizeWindow(Window *&win, int y, int x)
{
    TEFK_LOG_TRACE("Application::ResizeWindow({}, {}, {}, {})", V_PTR(this), V_PTR(win), y, x);

    ReconfigWindow(win, y, x, getbegy(win), getbegx(win));

    TEFK_LOG_TRACE("Application::ExitResizeWindow({})", V_PTR(this));
    return OK;
}

int Application::ReconfigWindow(Window *&win, int y, int x, int begy, int begx)
{
    TEFK_LOG_TRACE("Application::ReconfigWindow({}, {}, {}, {}, {}, {})", V_PTR(this), V_PTR(win), y, x, begy, begx);

    Window *temp;
    RET_IF_NIL(temp = newwin(y, x, begy, begx));
    RET_IF_ERR(wbkgd(temp, getbkgd(win)));
    RET_IF_ERR(delwin(win));
    win = temp;

    TEFK_LOG_TRACE("Application::ExitReconfigWindow({})", V_PTR(this));
    return OK;
}

} // namespace tefk
