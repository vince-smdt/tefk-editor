#pragma once
#include <filesystem>
#include <format>
#include <fstream>
#include <stdio.h>

namespace tefk {

class Logger {
private:
	std::ofstream file = {};
	std::ostream& stream;
public:
	explicit Logger(std::ostream& os)
		: stream{os}
	{}

	explicit Logger(std::filesystem::path& filename)
		: file(filename, std::ios::app),
		  stream{file}
	{}

	template <typename... Args>
	// TODO - change std::_Fmt_string<Args...> to std::format_string<Args...>
	void Log(const std::_Fmt_string<Args...> format, Args&&... args) {
		stream << std::format(format, std::forward<Args>(args)...) 
		       << std::endl;
	}
};

}