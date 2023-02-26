#include "app.hpp"

namespace tefk {

void Application::Init(int argc, char** argv) {
    ConsoleAPI::Init();
    _editor.OpenFiles(argc, argv);
    _appManager.OpenWindow(_editor);
}

void Application::Run() {
    _appManager.AddEvent(Event::ApplicationStart());
    while (_appManager.Running()) {
        _appManager.CatchEvents();
        _appManager.RunEvents();
    }
}

} // namespace tefk
