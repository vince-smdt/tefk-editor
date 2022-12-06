#pragma once
#include <fstream>
#include <stdio.h>

namespace tefk {

class Logger {
private:
	Logger() = delete;
	Logger(const Logger&) = delete;
public:
	static void Log(const char* message) {
		std::ofstream logfile("log.txt", std::ios::app);
		logfile << message << std::endl;
	}
};

}