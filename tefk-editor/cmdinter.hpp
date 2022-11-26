#pragma once
#include "editor.hpp"

namespace tefk {

class CommandLineArgsInterpreter {
private:
	CommandLineArgsInterpreter() = delete;
	CommandLineArgsInterpreter(const CommandLineArgsInterpreter&) = delete;
public:
	static void interpret(int argc, char** argv) {
		if (argc > 1) Editor::openOrCreateFiles(argc, argv);
		else Editor::newFile();
	}
};

}