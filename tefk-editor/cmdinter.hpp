#pragma once
#include "windows/editor.hpp" // TODO - include this logic in editor class or make editor class dependant of cmdinter namespace

namespace tefk::CommandLineArgsInterpreter {

static void Interpret(int argc, char** argv) {
	if (argc > 1) 
		Editor::Instance().OpenOrCreateFiles(argc, argv);
	else 
		Editor::Instance().NewFile();
}

}