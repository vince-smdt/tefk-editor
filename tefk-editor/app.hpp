#pragma once
#include <conio.h>
#include "cmdinter.hpp"
#include "consolemanager.hpp"

namespace tefk {

class Application {
private:
	static tefk::File* _currFile;
public:
	static void Init(int argc, char** argv) {
		SetConsoleCtrlHandler(NULL, TRUE);
		CommandLineArgsInterpreter::Interpret(argc, argv);

		_currFile = &tefk::Editor::CurrentFile();
	}

	static void Run() {
		ConsoleManager::RefreshConsole();
		while (true) {
			if (_kbhit()) {
				_currFile->Keypress(_getch()); // Change _getch() for function that can properly read Fn keys
				_currFile->Save();
				tefk::ConsoleManager::RefreshConsole();
			}
			if (tefk::ConsoleManager::ConsoleSizeChanged()) {
				tefk::ConsoleManager::RefreshConsole();
			}
		}
	}
};
tefk::File* Application::_currFile;

}