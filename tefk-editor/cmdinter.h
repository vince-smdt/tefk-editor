#pragma once
#include <iostream>

static class CommandLineArgsInterpreter {
private:
	CommandLineArgsInterpreter(){}
public:
	static void interpret(int argc, char** argv) {
		for (int i = 0; i < argc; i++) {
			std::cout << argv[i];
		}
	}
};