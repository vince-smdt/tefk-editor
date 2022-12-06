#pragma once
#include <fstream>
#include <sstream>

namespace tefk {

class File {
private:
	std::string _filename,
				_content;
public:
	// TODO - check if we have write access to file
	File(const std::string& filename) : _filename(filename) {
		std::ifstream file(filename);
		if (file) {
			// TODO - (maybe) optimize to avoid redundant copy https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
			std::ostringstream ss;
			ss << file.rdbuf();
			_content = ss.str();
		}
	}

	std::string GetFilename() {
		return _filename;
	}

	void SetFilename(std::string filename) {
		_filename = filename;
	}

	std::string GetContent() {
		return _content;
	}

	void SetContent(std::string content) {
		_content = content;
	}

	void Save() {
		std::ofstream file(_filename);
		file << _content;
	}
};

}