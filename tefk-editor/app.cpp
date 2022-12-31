#include "app.hpp"

namespace tefk {

void Application::Init(int argc, char** argv) {
	ConsoleAPI::Init();
	InterpretCommandLineArgs(argc, argv);
	ApplicationManager::OpenWindow(_editor);
}

void Application::Run() {
	ApplicationManager::Display();
	while (true) {
		ApplicationManager::CatchEvents();
		ApplicationManager::RunEvents();
	}
}

void Application::InterpretCommandLineArgs(int argc, char** argv) {
	if (argc > 1)
		_editor.OpenOrCreateFiles(argc, argv);
	else
		_editor.NewFile();
}

}