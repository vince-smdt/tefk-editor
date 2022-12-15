#pragma once
#include <filesystem>
#include <format>
#include <fstream>
#include <stdio.h>

namespace tefk {

class Logger {
private:
	std::ofstream _file;
	std::ostream& _stream;

	explicit Logger(std::filesystem::path& filename)
		: _file{ filename, std::ios::app },
		  _stream{_file}
	{}
public:
	static Logger& Instance() {
		static std::filesystem::path filename("log.txt");
		static Logger instance(filename);
		return instance;
	}

	template <typename... Args>
	void Log(const std::_Fmt_string<Args...> format, Args&&... args) {
		try {
			_stream << std::format(format, std::forward<Args>(args)...) 
			        << std::endl;
		}
		catch (std::ios_base::failure) {
			// TODO - Show error in console
		}
		catch (std::bad_alloc) {
			// ...
		}
	}
};

}