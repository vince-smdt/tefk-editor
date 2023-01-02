#include "appmanager.hpp"

namespace tefk {

std::stack<Window*> ApplicationManager::s_windows;
std::stack<std::shared_ptr<Event>> ApplicationManager::s_events;

void ApplicationManager::Display() {
	ConsoleManager::ResizeConsole();

	if (s_windows.empty()) {
		Logger::Instance().Log(
			Logger::LogLevel::WARN,
			"Cannot print current window, window stack empty. Proceeding to termination of application."
		);
		CloseApp();
	}

	s_windows.top()->Update();
	s_windows.top()->Print();
}

void ApplicationManager::OpenWindow(Window& window) {
	s_windows.push(&window);
}

void ApplicationManager::CloseWindow() {
	s_windows.pop();
	if (s_windows.empty()) {
		Logger::Instance().Log(
			Logger::LogLevel::TRACE,
			"Window stack empty. Proceeding to termination of application."
		);
		CloseApp();
	}
}

void ApplicationManager::CatchEvents() {
	if (_kbhit())
		AddEvent(Input::CatchInput());

	if (ConsoleManager::ConsoleSizeChanged())
		AddEvent(Event::ConsoleSizeChange());
}

void ApplicationManager::AddEvent(Event event) {
	s_events.push(std::make_shared<Event>(event));
}

void ApplicationManager::RunEvents() {
	// TODO - check if window stack empty, avoid redundancy in checks
	if (s_events.empty())
		return;

	while (!s_events.empty()) {
		ProcessEvent(*s_events.top());
		s_windows.top()->CatchAndPropagateEvent(*s_events.top());
		s_events.pop();
	}

	Display();
}

void ApplicationManager::ProcessEvent(Event& event) {
	if (event.type == Event::Type::CONSOLE_SIZE_CHANGE)
		ConsoleManager::ResizeConsole();
}

void ApplicationManager::CloseApp() {
	Logger::Instance().Log(
		Logger::LogLevel::INFO,
		"Closing application."
	);
	exit(0);
}

}