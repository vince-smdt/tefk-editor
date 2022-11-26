#include <conio.h>
#include <iostream>
#include "cmdinter.hpp"

int main(int argc, char** argv) {
	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File file = tefk::Editor::Files()[0]; // TODO - use index for current selected file (in case multiple files open)
	
	while (true) {
		if (_kbhit()) {
			file.keypress(_getche());
			system("cls");
			std::cout << file.content();
			file.save();
		}
	}

	return 0;
}