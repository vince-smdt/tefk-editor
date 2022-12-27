#pragma once
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <stdio.h>

namespace tefk {

// TODO - make implementation file, deal with Log method Args template
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

	explicit Logger(std::filesystem::path& filename)
		: _file{ filename, std::ios::app },
		  _stream{_file}
	{}

	std::string LogLevelStr(LogLevel level) {
		switch (level) {

		case LogLevel::FATAL:
			return "FATAL";

		case LogLevel::ERR:
			return "ERROR";

		case LogLevel::WARN:
			return "WARN";

		case LogLevel::INFO:
			return "INFO";

		case LogLevel::DEBUG:
			return "DEBUG";

		case LogLevel::TRACE:
			return "TRACE";

		}

		return "";
	}

	const std::string CurrentDateTime() {
		using namespace std::chrono;
		auto local = zoned_time{ current_zone(), system_clock::now() };
		return std::format("{:%F %T}", local);
	}
public:
	static Logger& Instance() {
		static std::filesystem::path filename("log.txt");
		static Logger instance(filename);
		return instance;
	}

	template <typename... Args>
	void Log(LogLevel level, const std::_Fmt_string<Args...> format, Args&&... args) {
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
};

}