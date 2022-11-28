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
			tefk::ConsoleManager::refreshConsole();
			file->save();
		}
	}
}