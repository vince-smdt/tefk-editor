#include <conio.h>
#include "cmdinter.hpp"
#include "consolemanager.hpp"

int main(int argc, char** argv) {
	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File *file = &tefk::Editor::CurrentFile();
	tefk::ConsoleManager::refreshConsole();

	while (true) {
		if (_kbhit()) {
			file->keypress(_getch());
			file->save();
			tefk::ConsoleManager::refreshConsole();
		}
		if (tefk::ConsoleManager::consoleSizeChanged()) {
			tefk::ConsoleManager::refreshConsole();
		}
	}
}