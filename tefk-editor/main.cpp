#include <conio.h>
#include <Windows.h>
#include "fileeditor.h"
#include "cmdinter.h"

int main(int argc, char** argv) {
	CommandLineArgsInterpreter::interpret(argc, argv);

	FileEditor editor("C://temp/test.txt");

	while (true) {
		if (_kbhit()) {
			editor.keypress(_getche());
			system("cls");
			std::cout << editor.content();
			editor.save();
		}
	}

	return 0;
}