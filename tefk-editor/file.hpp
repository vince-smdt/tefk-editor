#pragma once
#include <fstream>
#include <sstream>
#include <filesystem>

namespace tefk {

class File {
private:
	std::filesystem::path _filename;
	std::string _content;
public:
	File();

	std::filesystem::path GetFilename();
	std::string GetContent();

	void SetContent(std::string content);

	bool Open(std::filesystem::path& filename);
	void Save();
};

} // namespace tefk