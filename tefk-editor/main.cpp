#include <conio.h>
#include "cmdinter.hpp"
#include "consolemanager.hpp"

int main(int argc, char** argv) {
	SetConsoleCtrlHandler(NULL, TRUE);

	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File *file = &tefk::Editor::CurrentFile();
	tefk::ConsoleManager::refreshConsole();

	while (true) {
		if (_kbhit()) {
			file->keypress(_getch()); // Change _getch() for function that can properly read Fn keys
			file->save();
			tefk::ConsoleManager::refreshConsole();
		}
		if (tefk::ConsoleManager::consoleSizeChanged()) {
			tefk::ConsoleManager::refreshConsole();
		}
	}
}