#include "consolemanager.hpp"

namespace tefk {

int ConsoleManager::s_currRows = 0;
int ConsoleManager::s_currCols = 0;

bool ConsoleManager::ConsoleSizeChanged() {
	return s_currRows != ConsoleAPI::GetConsoleSize().Y || s_currCols != ConsoleAPI::GetConsoleSize().X;
}

void ConsoleManager::ResizeConsole() {
	s_currRows = ConsoleAPI::GetConsoleSize().Y;
	s_currCols = ConsoleAPI::GetConsoleSize().X;

	ConsoleAPI::SetConsoleSize(s_currRows, s_currCols);
}

} // namespace tefk