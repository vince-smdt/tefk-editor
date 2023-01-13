#include "appmanager.hpp"

namespace tefk::ApplicationManager {

void Render() {
	ConsoleManager::ResizeConsole();

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

void OpenWindow(Window& window) {
	_windows.push(&window);
}

void CloseWindow() {
	_windows.pop();
	if (_windows.empty()) {
		Logger::Instance().Log(
			Logger::LogLevel::TRACE,
			"Window stack empty. Proceeding to termination of application."
		);
		CloseApp();
	}
}

void CatchEvents() {
	if (_kbhit())
		AddEvent(Input::CatchInput());

	if (ConsoleManager::ConsoleSizeChanged())
		AddEvent(Event::ConsoleSizeChange());
}

void AddEvent(Event event) {
	_events.push(std::make_shared<Event>(event));
}

void RunEvents() {
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

void ProcessEvent(Event& event) {
	if (event.type == Event::Type::CONSOLE_SIZE_CHANGE)
		ConsoleManager::ResizeConsole();
}

void CloseApp() {
	Logger::Instance().Log(
		Logger::LogLevel::INFO,
		"Closing application."
	);
	exit(0);
}

} // namespace tefk