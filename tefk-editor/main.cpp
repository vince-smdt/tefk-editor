#include <iostream>
#include <conio.h>
#include <vector>

int main() {
	std::string contents = "";
	char ch;

	while (true) {
		ch = _getch();
		contents += ch;
		system("cls");
		std::cout << contents;
	}

	return 0;
}