#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "fileeditor.h"

int main() {
	FileEditor editor("C://temp/test.txt");

	while (true) {
		if (_kbhit()) {
			editor.keypress(_getche());
			system("cls");
			std::cout << editor.getFileContent();
			editor.save();
		}
	}

	return 0;
}