#pragma once
#include <vector>
#include "file.hpp"

namespace tefk {

class Editor {
private:
	Editor() = delete;
	Editor(const Editor&) = delete;

	static std::vector<File> s_files;
public:
	static std::vector<File>& Files() {
		return s_files;
	}

	static void newFile() {
		s_files.push_back(File("new.txt")); // TODO - prompt user to enter filename
	}

	static void openOrCreateFiles(int filecount, char** filenames) {
		for (int i = 1; i < filecount; i++) {
			s_files.push_back(File(filenames[i]));
		}
	}
};
std::vector<File> Editor::s_files;

}

