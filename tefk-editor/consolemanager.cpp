#include "consolemanager.hpp"

namespace tefk {

int ConsoleManager::s_currRows = 0;
int ConsoleManager::s_currCols = 0;
std::shared_ptr<Window> ConsoleManager::s_window;
TextColor ConsoleManager::_defaultColor = { BLACK, WHITE };
TextColor ConsoleManager::_headerColor = { WHITE, BLACK };
TextColor ConsoleManager::_contentColor = { BLACK, WHITE };
TextColor ConsoleManager::_footerColor = { WHITE, BLACK };

void ConsoleManager::Init() {
	s_window = Designer::Editor();
}

bool ConsoleManager::ConsoleSizeChanged() {
	return s_currRows != ConsoleAPI::RowCount() || s_currCols != ConsoleAPI::ColCount();
}

void ConsoleManager::Print(std::string text, TextColor color) {
	ConsoleAPI::SetTextColor(color);

	if (text.size() > ConsoleAPI::ColCount())
		text = text.substr(0, ConsoleAPI::ColCount() - 1);
	std::cout << text << FillRow;

	ConsoleAPI::SetTextColor(_defaultColor);
}

void ConsoleManager::PrintHeader() {
	ConsoleAPI::SetCursorPos(0, 0);

	std::stringstream ss;
	ss << Editor::CurrentFile().GetFilename() << " "
		<< Editor::FileIndex() + 1 << "/"
		<< Editor::Files().size() << " "
		<< "Press Ctrl+S to save!";
	Print(ss.str(), _headerColor);
}

void ConsoleManager::PrintContent() {
	// TODO - Only print content that fits in the console, rest can be seen by scrolling
	ConsoleAPI::SetCursorPos(2, 0);

	std::stringstream ss;
	ss << Editor::CurrentFile().GetContent();
	Print(ss.str(), _contentColor);
}

void ConsoleManager::PrintFooter() {
	ConsoleAPI::SetCursorPos(ConsoleAPI::RowCount() - 1, 0);

	std::stringstream ss;
	ss << "Rows = " << ConsoleAPI::RowCount()
		<< ", Cols = " << ConsoleAPI::ColCount();
	Print(ss.str(), _footerColor);
}

std::ostream& ConsoleManager::FillRow(std::ostream& stream) {
	return stream << std::string(ConsoleAPI::ColCount() - ConsoleAPI::CursorColPos(), ' ');
}

void ConsoleManager::RefreshConsole() {
	// TODO - Reset entire console color in case previous color before app starts
	s_currRows = ConsoleAPI::RowCount();
	s_currCols = ConsoleAPI::ColCount();

	// TODO - Maybe resize console after clearing it to avoid console resize error
	ConsoleAPI::SetConsoleSize(s_currRows, s_currCols);

	ConsoleAPI::ClearConsole();

	PrintHeader();
	PrintContent();
	PrintFooter();

	s_window->Print();
}

}