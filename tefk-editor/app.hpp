#pragma once
#include <conio.h>
#include "cmdinter.hpp"
#include "consolemanager.hpp"

namespace tefk {

class Application {
private:
	static tefk::File* _currFile;
public:
	static void init(int argc, char** argv) {
		SetConsoleCtrlHandler(NULL, TRUE);
		CommandLineArgsInterpreter::interpret(argc, argv);

		_currFile = &tefk::Editor::CurrentFile();
	}

	static void run() {
		ConsoleManager::refreshConsole();
		while (true) {
			if (_kbhit()) {
				_currFile->keypress(_getch()); // Change _getch() for function that can properly read Fn keys
				_currFile->save();
				tefk::ConsoleManager::refreshConsole();
			}
			if (tefk::ConsoleManager::consoleSizeChanged()) {
				tefk::ConsoleManager::refreshConsole();
			}
		}
	}
};
tefk::File* Application::_currFile;

}