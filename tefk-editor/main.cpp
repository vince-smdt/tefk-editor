#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>

int main() {
	std::string contents = "";
	char ch;

	while (true) {
		ch = _getch();

		if (ch == VK_BACK) {
			if (contents.size()) contents.erase(contents.size() - 1);
		}
		else if (ch == VK_RETURN) {
			contents += '\n';
		}
		else {
			contents += ch;
		}

		system("cls");
		std::cout << contents;
	}

	return 0;
}