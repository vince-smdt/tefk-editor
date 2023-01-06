#pragma once
#include <conio.h>

#include "gui/appmanager.hpp"
#include "windows/editor.hpp"

namespace tefk {

class Application {
	Editor _editor;
public:
	void Init(int argc, char** argv);
	void Run();
private:
	void InterpretCommandLineArgs(int argc, char** argv);
};

} // namespace tefk