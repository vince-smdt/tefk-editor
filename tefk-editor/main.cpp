#include <conio.h>

#include "application.hpp"
#include "windows/editor.hpp"

int main(int argc, char** argv) {
    tefk::Application _appManager;
    tefk::Editor _editor;

    tefk::ConsoleAPI::Init();
    _editor.OpenFiles(argc, argv);
    _appManager.OpenWindow(_editor);

    _appManager.AddEvent(tefk::Event::ApplicationStart()); // TODO - automatically create this event upon application start internally, maybe start method for app?
    while (_appManager.Running()) {
        _appManager.CatchEvents();
        _appManager.RunEvents();
    }
}
