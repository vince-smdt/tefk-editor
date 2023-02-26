#include "appmanager.hpp"

namespace tefk {

ApplicationManager::ApplicationManager()
    : _running{ true }
{}

Canvas& ApplicationManager::GetCanvas() {
    return _canvas;
}

void ApplicationManager::OpenWindow(Window& window) {
    _windows.push(&window);
    window.SetParent(*this);
}

void ApplicationManager::CloseWindow() {
    _windows.pop();
    if (_windows.empty()) {
        Logger::Instance().Log(
            Logger::LogLevel::TRACE,
            "Window stack empty. Proceeding to termination of application."
        );
        CloseApp();
    }
}

void ApplicationManager::CatchEvents() {
    if (_windows.top()->IsClosing())
        AddEvent(Event::WindowClosing());

    if (_windows.top()->ExecuteTimerBoundProcedures())
        AddEvent(Event::TimerUp());

    if (_kbhit())
        AddEvent(Input::CatchInput());

    if (ConsoleAPI::ConsoleSizeChanged())
        AddEvent(Event::ConsoleSizeChange());
}

void ApplicationManager::AddEvent(Event event) {
    _events.push(std::make_shared<Event>(event));
}

void ApplicationManager::RunEvents() {
    // TODO - check if window stack empty, avoid redundancy in checks
    if (_events.empty())
        return;

    while (!_events.empty()) {
        ProcessEvent(*_events.front());
        if (_windows.top()->IsClosing()) {
            CloseWindow();
            return;
        }
        _windows.top()->CatchAndPropagateEvent(*_events.front());
        _events.pop();
    }

    Render();
}

void ApplicationManager::ProcessEvent(Event event) {
    if (event.type == Event::Type::CONSOLE_SIZE_CHANGE)
        ConsoleAPI::UpdateConsoleSize();

    if (event.type == Event::Type::WINDOW_CLOSING)
        _windows.top()->Close();
}

void ApplicationManager::Render() {
    if (_windows.empty()) {
        Logger::Instance().Log(
            Logger::LogLevel::WARN,
            "Cannot render current window, window stack empty. Proceeding to termination of application."
        );
        CloseApp();
    }
    
    _windows.top()->UpdateComponents();
    _windows.top()->Render();
}

bool ApplicationManager::Running() {
    return _running;
}

void ApplicationManager::CloseApp() {
    Logger::Instance().Log(
        Logger::LogLevel::INFO,
        "Closing application."
    );
    _running = false;
}

} // namespace tefk
