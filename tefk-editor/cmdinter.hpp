#pragma once
#include "editor.hpp"

namespace tefk::CommandLineArgsInterpreter {
	static void Interpret(int argc, char** argv) {
		if (argc > 1) 
			Editor::OpenOrCreateFiles(argc, argv);
		else 
			Editor::NewFile();
	}
}