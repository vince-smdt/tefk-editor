#include <conio.h>
#include <iostream>
#include "cmdinter.hpp"

int main(int argc, char** argv) {
	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File *file = &tefk::Editor::CurrentFile();

	while (true) {
		if (_kbhit()) {
			file->keypress(_getche());
			tefk::Editor::print();
			file->save();
		}
	}

	return 0;
}