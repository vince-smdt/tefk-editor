#pragma once
#include <conio.h>
#include "cmdinter.hpp"
#include "gui/appmanager.hpp"
#include "keypresshandler.hpp"

namespace tefk {

class Application {
	Editor _editor;
public:
	void Init(int argc, char** argv);
	void Run();
};

}