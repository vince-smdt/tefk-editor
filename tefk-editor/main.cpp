#include <conio.h>
#include <iostream>
#include "cmdinter.hpp"

int main(int argc, char** argv) {
	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File file = tefk::Editor::CurrentFile();

	while (true) {
		if (_kbhit()) {
			file.keypress(_getche());
			system("cls");
			std::cout 
				<< file.filename() << " " << tefk::Editor::FileIndex()+1 << "/" << tefk::Editor::Files().size()
				<< std::endl << std::endl
				<< file.content();
			file.save();
		}
	}

	return 0;
}