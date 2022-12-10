#pragma once
#include <filesystem>
#include <format>
#include <fstream>
#include <stdio.h>

namespace tefk {

class Logger {
private:
	Logger() = delete;
	Logger(const Logger&) = delete;
public:
	template <class... FormatArgs>
	static void Log(const std::string_view format, FormatArgs&&... args) {
		std::ofstream logfile("log.txt", std::ios::app);
		logfile << std::vformat(format, std::make_format_args(args...)) << std::endl;
	}
};

}