#include "application.hpp"

namespace tefk {

Application::Application()
    : _running{ true }
{}

Canvas& Application::GetCanvas() {
    return _canvas;
}

void Application::OpenWindow(Window& window) {
    _windows.push(&window);
    window.SetParent(*this);
    window.Open();
}

void Application::CloseWindow() {
    _windows.pop();
    if (_windows.empty()) {
        Logger::Instance().Log(
            Logger::LogLevel::TRACE,
            "Window stack empty. Proceeding to termination of application."
        );
        CloseApp();
    }
}

void Application::CatchEvents() {
    if (_windows.top()->IsClosing())
        AddEvent(Event::WindowClosing());

    if (_windows.top()->ExecuteTimerBoundProcedures())
        AddEvent(Event::TimerUp());

    if (_kbhit())
        AddEvent(CatchInput());

    if (ConsoleAPI::ConsoleSizeChanged())
        AddEvent(Event::ConsoleSizeChange());
}

void Application::AddEvent(Event event) {
    _events.push(std::make_shared<Event>(event));
}

void Application::RunEvents() {
    // TODO - check if window stack empty, avoid redundancy in checks
    if (_events.empty())
        return;

    while (!_events.empty()) {
        ProcessEvent(*_events.front());
        _windows.top()->CatchAndPropagateEvent(*_events.front());
        _events.pop();
    }

    Render();
}

void Application::ProcessEvent(Event event) {
    if (event.type == Event::Type::CONSOLE_SIZE_CHANGE)
        ConsoleAPI::UpdateConsoleSize();

    if (event.type == Event::Type::WINDOW_CLOSING)
        CloseWindow();
}

void Application::Render() {
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

bool Application::Running() {
    return _running;
}

void Application::CloseApp() {
    Logger::Instance().Log(
        Logger::LogLevel::INFO,
        "Closing application."
    );
    _running = false;
}

} // namespace tefk
