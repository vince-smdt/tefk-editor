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
	File(std::filesystem::path& filename);

	std::filesystem::path GetFilename();
	std::string GetContent();

	void SetFilename(std::filesystem::path& filename);
	void SetContent(std::string content);

	void Save();
};

} // namespace tefk