#pragma once
#include <fstream>
#include <sstream>
#include "keypresshandler.hpp"

namespace tefk {

class File {
private:
	std::string _filename,
				_content;
public:
	// TODO - check if we have write access to file
	File(const std::string& filename) : _filename(filename), _content("") {
		std::ifstream file(filename);
		if (file) {
			// TODO - (maybe) optimize to avoid redundant copy https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
			std::ostringstream sstr;
			sstr << file.rdbuf();
			_content = sstr.str();
		}
	}

	std::string filename() const {
		return _filename;
	}

	std::string content() const {
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