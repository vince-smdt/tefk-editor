#include "app.hpp"

namespace tefk {

void Application::Init(int argc, char** argv) {
	ConsoleAPI::Init();
	_editor.OpenFiles(argc, argv);
	ApplicationManager::OpenWindow(_editor);
}

void Application::Run() {
	ApplicationManager::AddEvent(Event::ApplicationStart());
	while (ApplicationManager::Running()) {
		ApplicationManager::CatchEvents();
		ApplicationManager::RunEvents();
	}
}

} // namespace tefk