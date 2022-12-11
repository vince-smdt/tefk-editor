#pragma once
#include <conio.h>
#include "cmdinter.hpp"
#include "consolemanager.hpp"
#include "keypresshandler.hpp"

namespace tefk {

class Application {
private:
	static tefk::File* s_currFile;
public:
	static void Init(int argc, char** argv) {
		SetConsoleCtrlHandler(NULL, TRUE);
		CommandLineArgsInterpreter::Interpret(argc, argv);

		s_currFile = &tefk::Editor::CurrentFile();
	}

	static void Run() {
		ConsoleManager::RefreshConsole();
		while (true) {
			if (_kbhit()) {
				// Change _getch() for function that can properly read Fn keys
				// Change _getch() for function that can read letters with accents (Ex. é, è, ô, ï, ...)
				tefk::KeyPressHandler::HandleKeyPress(_getch());
				s_currFile->Save();
				tefk::ConsoleManager::RefreshConsole();
			}
			if (tefk::ConsoleManager::ConsoleSizeChanged()) {
				tefk::ConsoleManager::RefreshConsole();
			}
		}
	}
};
tefk::File* Application::s_currFile;

}