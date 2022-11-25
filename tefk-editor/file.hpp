#pragma once
#include <fstream>
#include "keypresshandler.hpp"

namespace tefk {

class File {
private:
	std::ofstream _file;
	std::string _filename,
		_content;
public:
	File(const std::string& filename) {
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
		tefk::KeyPressHandler::handleKeyPress(ch, _content);
	}
};

}