#pragma once
#include <fstream>
#include "keypresshandler.hpp"

namespace tefk {

class File {
private:
	std::string _filename,
				_content;
public:
	File(const std::string& filename) {
		_filename = filename; // TODO - check if we have write access to file
		_content = "";
	}

	std::string content() {
		return _content;
	}

	void save() {
		std::ofstream file(_filename);
		file << _content;
		file.close();
	}

	void keypress(char ch) {
		tefk::KeyPressHandler::handleKeyPress(ch, _content);
	}
};

}