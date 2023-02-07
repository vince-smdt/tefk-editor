#include "file.hpp"

namespace tefk {

File::File() {}

std::filesystem::path File::GetFilename() {
	return _filename;
}

TefkString File::GetContent() {
	return _content;
}

bool File::IsNewFile() {
	return _filename.empty();
}

void File::SetContent(TefkString content) {
	_content = content;
}

bool File::Open(std::filesystem::path filename) {
	// If file doesn't exist
	if (!std::filesystem::exists(filename)) {
		std::ofstream { filename };
		if (!std::filesystem::exists(filename)) {
			return false;
		}
		else {
			_filename = filename;
			return true;
		}
	}

	std::ifstream file(filename);

	// If we have access to file
	if (file) {
		std::ostringstream ss;
		ss << file.rdbuf();
		_filename = filename;
		_content = ss.str();
		return true;
	}

	// If we don't have access to file
	return false;
}

void File::Save() {
	std::ofstream file(_filename);
	file << _content;
}

} // namespace tefk