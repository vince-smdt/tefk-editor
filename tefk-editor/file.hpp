#pragma once
#include "gui/types.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace tefk {

class File {
private:
	std::filesystem::path _filename;
	TefkString _content;
public:
	File();

	std::filesystem::path GetFilename();
	TefkString GetContent();
	bool IsNewFile();

	void SetContent(TefkString content);

	bool Open(std::filesystem::path filename);
	void Save();
};

} // namespace tefk