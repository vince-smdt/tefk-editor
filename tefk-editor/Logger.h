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
    enum LogLevel {
        FATAL, 
        ERRNO, 
        WARN,
        INFO,
        DEBUG,
        TRACE
    };
public:
    static Logger& Instance();

    template <typename... Args>
    void Log(LogLevel level, const std::_Fmt_string<Args...> format, Args&&... args);
private:
    Logger(std::filesystem::path& filename);
    std::string LogLevelStr(LogLevel level);
    const std::string CurrentDateTime();

    std::ofstream _file;
    std::ostream& _stream;
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

#define TEFK_LOG_FATAL(msg, ...) Logger::Instance().Log(Logger::FATAL, msg __VA_OPT__(,)__VA_ARGS__)
#define TEFK_LOG_ERR(msg, ...)   Logger::Instance().Log(Logger::ERRNO, msg __VA_OPT__(,)__VA_ARGS__)
#define TEFK_LOG_WARN(msg, ...)  Logger::Instance().Log(Logger::WARN,  msg __VA_OPT__(,)__VA_ARGS__)
#define TEFK_LOG_INFO(msg, ...)  Logger::Instance().Log(Logger::INFO,  msg __VA_OPT__(,)__VA_ARGS__)
#define TEFK_LOG_DEBUG(msg, ...) Logger::Instance().Log(Logger::DEBUG, msg __VA_OPT__(,)__VA_ARGS__)
#define TEFK_LOG_TRACE(msg, ...) Logger::Instance().Log(Logger::TRACE, msg __VA_OPT__(,)__VA_ARGS__)

} // namespace tefk
