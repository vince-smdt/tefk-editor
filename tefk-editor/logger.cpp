#include "logger.hpp"

namespace tefk {

Logger::Logger(std::filesystem::path& filename)
	: _file{ filename, std::ios::app },
	_stream{ _file }
{}

std::string Logger::LogLevelStr(LogLevel level) {
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

	default:
		return "";

	}
}

const std::string Logger::CurrentDateTime() {
	using namespace std::chrono;
	auto local = zoned_time{ current_zone(), system_clock::now() };
	return std::format("{:%F %T}", local);
}

Logger& Logger::Instance() {
	static std::filesystem::path filename("log.txt");
	static Logger instance(filename);
	return instance;
}

}