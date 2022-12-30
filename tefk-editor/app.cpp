#include "app.hpp"

namespace tefk {

void Application::Init(int argc, char** argv) {
	ConsoleAPI::Init();
	CommandLineArgsInterpreter::Interpret(argc, argv);
	ApplicationManager::OpenWindow(_editor);
}

void Application::Run() {
	ApplicationManager::Display();
	while (true) {
		ApplicationManager::CatchEvents();
		ApplicationManager::RunEvents();
	}
}

}