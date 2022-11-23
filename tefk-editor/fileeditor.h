#pragma once
#include <fstream>

class FileEditor {
private:
	std::ofstream file;
	std::string content;
public:
	FileEditor(const std::string &fileName) {
		file = std::ofstream(fileName);
		content = "";
	}

	~FileEditor() {
		file.close();
	}

	std::string getFileContent() {
		return content;
	}

	void openFile(const std::string &fileName) {
		file.open(fileName);
	}

	void save() {
		file << content;
	}

	void erase(int i) {
		if (content.size()) content.erase(content.size() - 1);
	}

	void keypress(char ch) {
		switch (ch) {
		case VK_BACK:
			if (content.size()) content.erase(content.size() - 1);
			break;
		case VK_RETURN:
			content += '\n';
			break;
		default:
			content += ch;
			break;
		}
	}
};