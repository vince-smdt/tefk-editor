#pragma once
#include <fstream>

class FileEditor {
private:
	std::ofstream _file;
	std::string _filename,
				_content;
public:
	FileEditor(const std::string &filename) {
		_filename = filename;
		_content = "";
	}

	std::string content() {
		return _content;
	}

	void save() {
		_file.open(_filename, std::ios::trunc);
		_file << _content;
		_file.close();
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