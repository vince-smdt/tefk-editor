#include <conio.h>
#include "file.hpp"
#include "cmdinter.hpp"

int main(int argc, char** argv) {
	tefk::CommandLineArgsInterpreter::interpret(argc, argv);

	tefk::File file("C://temp/test.txt");
	
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