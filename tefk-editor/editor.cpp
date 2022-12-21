#include "editor.hpp"

namespace tefk {

std::vector<File> Editor::s_files;
std::vector<File>::size_type Editor::s_file_index;

std::vector<File>& Editor::Files() {
	return s_files;
}

File& Editor::CurrentFile() {
	return s_files[s_file_index];
}

std::vector<File>::size_type& Editor::FileIndex() {
	return s_file_index;
}

void Editor::NewFile() { // TODO - rename functions or fuse newfile with openorcreatefiles
	std::filesystem::path filepath("new.txt");
	s_files.push_back(File(filepath)); // TODO - prompt user to enter filename
	s_file_index = s_files.size() - 1;
}

void Editor::OpenOrCreateFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		s_files.push_back(File(filepath));
	}
	s_file_index = s_files.size() - (filecount + 1);
}

}