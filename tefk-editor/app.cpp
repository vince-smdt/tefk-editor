#include "app.hpp"

namespace tefk {

tefk::File* Application::s_currFile;

void Application::Init(int argc, char** argv) {
	ConsoleAPI::Init();
	CommandLineArgsInterpreter::Interpret(argc, argv);

	s_currFile = &tefk::Editor::CurrentFile();

	ConsoleManager::Init();
}

void Application::Run() {
	ConsoleManager::RefreshConsole();
	while (true) {
		if (_kbhit()) {
			// Change _getch() for function that can properly read Fn keys
			// Change _getch() for function that can read letters with accents (Ex. é, è, ô, ï, ...)
			tefk::KeyPressHandler::HandleKeyPress(_getch());
			tefk::ConsoleManager::RefreshConsole();
		}
		if (tefk::ConsoleManager::ConsoleSizeChanged()) {
			tefk::ConsoleManager::RefreshConsole();
		}
	}
}

}