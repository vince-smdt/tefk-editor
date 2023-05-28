#include "Application.h"

#include <curses.h>

int main(int argc, char **argv)
{
    tefk::Application app;
    app.Initialize();
    app.Run();
    app.Finalize();
}
