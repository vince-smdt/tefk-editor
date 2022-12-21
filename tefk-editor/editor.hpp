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
	static std::vector<File>& Files();
	static File& CurrentFile();
	static std::vector<File>::size_type& FileIndex();

	static void NewFile();
	static void OpenOrCreateFiles(int filecount, char** filenames);
};

}

