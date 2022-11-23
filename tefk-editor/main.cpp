#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>

void handleKeyPress(std::string &contents);

int main() {
	std::string contents = "";
	char ch;

	while (true) {
		if (_kbhit()) {
			handleKeyPress(contents);
			system("cls");
			std::cout << contents;
		}
	}

	return 0;
}

void handleKeyPress(std::string &contents) {
	char ch = _getch();

	switch (ch) {
	case VK_BACK:
		if (contents.size()) contents.erase(contents.size() - 1);
		break;
	case VK_RETURN:
		contents += '\n';
		break;
	default:
		contents += ch;
		break;
	}
}