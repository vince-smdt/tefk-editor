#pragma once
#include <vector>
#include "file.hpp"

namespace tefk { 

class Editor {
private:
	Editor() = delete;
	Editor(const Editor&) = delete;

	static std::vector<File> s_files;
	static std::vector<File>::size_type s_file_index;
public:
	static std::vector<File>& Files() {
		return s_files;
	}

	static File& CurrentFile() {
		return s_files[s_file_index];
	}

	static std::vector<File>::size_type& FileIndex() {
		return s_file_index;
	}

	static void NewFile() {
		s_files.push_back(File("new.txt")); // TODO - prompt user to enter filename
		s_file_index = s_files.size() - 1;
	}

	static void OpenOrCreateFiles(int filecount, char** filenames) {
		for (int i = 1; i < filecount; i++)
			s_files.push_back(File(filenames[i]));
		s_file_index = s_files.size() - (filecount + 1);
	}
};
std::vector<File> Editor::s_files;
std::vector<File>::size_type Editor::s_file_index;

}

