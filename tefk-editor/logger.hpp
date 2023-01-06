#pragma once
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <stdio.h>

namespace tefk {

// TODO - make implementation file, deal with Log method Args template
// TODO - fix first log that creates file always has error code 0 (GetLastError() - WinAPI)
class Logger {
public:
	enum class LogLevel {
		FATAL, 
		ERR, 
		WARN,
		INFO,
		DEBUG,
		TRACE
	};
private:
	std::ofstream _file;
	std::ostream& _stream;

	explicit Logger(std::filesystem::path& filename);

	std::string LogLevelStr(LogLevel level);
	const std::string CurrentDateTime();
public:
	static Logger& Instance();

	template <typename... Args>
	void Log(LogLevel level, const std::_Fmt_string<Args...> format, Args&&... args);
};


template <typename... Args>
inline void Logger::Log(LogLevel level, const std::_Fmt_string<Args...> format, Args&&... args) {
	try {
		_stream << CurrentDateTime() << " "
			<< std::setw(5) << std::left << LogLevelStr(level) << " "
			<< std::format(format, std::forward<Args>(args)...)
			<< std::endl;
	}
	catch (std::ios_base::failure) {
		// TODO - Show error in console
	}
	catch (std::bad_alloc) {
		// ...
	}
}

} // namespace tefk