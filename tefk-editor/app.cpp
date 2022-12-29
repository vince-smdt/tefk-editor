#include "app.hpp"

namespace tefk {

void Application::Init(int argc, char** argv) {
	ConsoleAPI::Init();
	CommandLineArgsInterpreter::Interpret(argc, argv);
	ConsoleManager::OpenWindow(_editor);
}

void Application::Run() {
	ConsoleManager::RefreshConsole();
	while (true) {
		if (_kbhit()) {
			// TODO - Change _getch() for function that can properly read Fn keys
			// TODO - Change _getch() for function that can read letters with accents (Ex. é, è, ô, ï, ...)
			tefk::KeyPressHandler::HandleKeyPress(_getch());
			tefk::ConsoleManager::RefreshConsole();
		}
		if (tefk::ConsoleManager::ConsoleSizeChanged()) {
			tefk::ConsoleManager::RefreshConsole();
		}
	}
}

}