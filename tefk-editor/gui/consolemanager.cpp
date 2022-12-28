#include "consolemanager.hpp"

namespace tefk {

int ConsoleManager::s_currRows = 0;
int ConsoleManager::s_currCols = 0;
std::stack<std::shared_ptr<Window>> ConsoleManager::s_windows;

void ConsoleManager::OpenWindow(std::shared_ptr<Window> window) {
	s_windows.push(window);
}

void ConsoleManager::CloseWindow() {
	s_windows.pop();
	if (s_windows.empty()) {
		Logger::Instance().Log(
			Logger::LogLevel::TRACE,
			"Window stack empty. Proceeding to termination of application."
		);
		CloseApp();
	}
}

void ConsoleManager::CloseApp() {
	Logger::Instance().Log(
		Logger::LogLevel::INFO,
		"Closing application."
	);
	exit(0);
}

bool ConsoleManager::ConsoleSizeChanged() {
	return s_currRows != ConsoleAPI::RowCount() || s_currCols != ConsoleAPI::ColCount();
}

void ConsoleManager::RefreshConsole() {
	// TODO - Reset entire console color in case previous color before app starts
	s_currRows = ConsoleAPI::RowCount();
	s_currCols = ConsoleAPI::ColCount();

	ConsoleAPI::SetConsoleSize(s_currRows, s_currCols);

	if (s_windows.empty()) {
		Logger::Instance().Log(
			Logger::LogLevel::WARN,
			"Cannot print current window, window stack empty. Proceeding to termination of application."
		);
		CloseApp();
	}

	s_windows.top()->Print();
}

}