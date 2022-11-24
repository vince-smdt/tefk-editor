#pragma once
#include <fstream>

class FileEditor {
private:
	std::ofstream _file;
	std::string _content;
public:
	FileEditor(const std::string &fileName) {
		_file = std::ofstream(fileName);
		_content = "";
	}

	std::string content() {
		return _content;
	}

	void save() {
		_file << _content << std::flush;
	}

	void keypress(char ch) {
		switch (ch) {
		case VK_BACK:
			if (_content.size()) _content.erase(_content.size() - 1);
			break;
		case VK_RETURN:
			_content += '\n';
			break;
		default:
			_content += ch;
			break;
		}
	}
};