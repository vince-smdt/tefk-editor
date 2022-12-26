#pragma once
#include <conio.h>
#include "cmdinter.hpp"
#include "gui/consolemanager.hpp"
#include "keypresshandler.hpp"

namespace tefk {

class Application {
private:
	static tefk::File* s_currFile;
public:
	static void Init(int argc, char** argv);
	static void Run();
};

}