#include "file.hpp"

namespace tefk {

File::File(std::filesystem::path& filename) 
	: _filename{ filename }
{
	std::ifstream file(filename);
	// TODO - check if we have write access to file
	if (file) {
		// TODO - (maybe) optimize to avoid redundant copy https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
		std::ostringstream ss;
		ss << file.rdbuf();
		_content = ss.str();
	}
}

std::filesystem::path File::GetFilename() {
	return _filename;
}

void File::SetFilename(std::filesystem::path& filename) {
	_filename = filename;
}

std::string File::GetContent() {
	return _content;
}

void File::SetContent(std::string content) {
	_content = content;
}

void File::Save() {
	std::ofstream file(_filename);
	file << _content;
}

} // namespace tefk