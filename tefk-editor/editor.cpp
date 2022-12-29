#include "editor.hpp"

namespace tefk {

Editor& Editor::Instance() {
	static Editor editor;
	return editor;
}

std::vector<File>& Editor::Files() {
	return _files;
}

File& Editor::CurrentFile() {
	return _files[_file_index];
}

std::vector<File>::size_type& Editor::FileIndex() {
	return _file_index;
}

void Editor::NewFile() { // TODO - rename functions or fuse newfile with openorcreatefiles
	std::filesystem::path filepath("new.txt");
	_files.push_back(File(filepath)); // TODO - prompt user to enter filename
	_file_index = _files.size() - 1;
}

void Editor::OpenOrCreateFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		_files.push_back(File(filepath));
	}
	_file_index = _files.size() - (filecount + 1);
}

}