#pragma once
#include <iostream>
#include <memory>
#include "editor.hpp"
#include "gui-components/panel.hpp"
#include "gui-components/label.hpp"
#include "gui-components/textfield.hpp"

namespace tefk {


class ConsoleManager {
private:
	ConsoleManager() = delete;
	ConsoleManager(const ConsoleManager&) = delete;

	static int s_currRows;
	static int s_currCols;

	static std::shared_ptr<Panel> s_guitest;

	// TODO - make these constants
	static TextColor _defaultColor;
	static TextColor _headerColor;
	static TextColor _contentColor;
	static TextColor _footerColor;
public:
	static void Init() {
		s_guitest = std::make_shared<Panel>();
		s_guitest->SetSize({ 26, 4 });
		s_guitest->SetColor({ BLUE, WHITE });
		s_guitest->SetPosition({ 40, 20 });
		
		std::shared_ptr<Label> lbl = std::make_shared<Label>();
		lbl->SetSize({ 26, 2 });
		lbl->SetColor({ BLUE, WHITE });
		lbl->SetPosition({ 0, 0 });
		lbl->SetText("This is a test label.");

		std::shared_ptr<TextField> txt = std::make_shared<TextField>();
		txt->SetSize({ 26, 2 });
		txt->SetColor({ BLUE, WHITE });
		txt->SetPosition({ 0, 2 });
		txt->AddText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbccc");

		s_guitest->AddComponent(lbl);
		s_guitest->AddComponent(txt);
	}

	static bool ConsoleSizeChanged() {
		return s_currRows != ConsoleAPI::RowCount() || s_currCols != ConsoleAPI::ColCount();
	}

	static void Print(std::string text, TextColor color) {
		ConsoleAPI::SetTextColor(color);

		if (text.size() > ConsoleAPI::ColCount())
			text = text.substr(0, ConsoleAPI::ColCount() - 1);
		std::cout << text << FillRow;

		ConsoleAPI::SetTextColor(_defaultColor);
	}

	static void PrintHeader() {
		ConsoleAPI::SetCursorPos(0, 0);

		std::stringstream ss;
		ss << Editor::CurrentFile().GetFilename() << " "
		   << Editor::FileIndex() + 1 << "/"
		   << Editor::Files().size() << " "
		   << "Press Ctrl+S to save!";
		Print(ss.str(), _headerColor);
	}

	static void PrintContent() {
		// TODO - Only print content that fits in the console, rest can be seen by scrolling
		ConsoleAPI::SetCursorPos(2, 0);

		std::stringstream ss;
		ss << Editor::CurrentFile().GetContent();
		Print(ss.str(), _contentColor);
	}

	static void PrintFooter() {
		ConsoleAPI::SetCursorPos(ConsoleAPI::RowCount() - 1, 0);

		std::stringstream ss;
		ss << "Rows = " << ConsoleAPI::RowCount() 
		   << ", Cols = " << ConsoleAPI::ColCount();
		Print(ss.str(), _footerColor);
	}

	static std::ostream& FillRow(std::ostream& stream) {
		return stream << std::string(ConsoleAPI::ColCount() - ConsoleAPI::CursorColPos(), ' ');
	}

	static void RefreshConsole() {
		// TODO - Reset entire console color in case previous color before app starts
		s_currRows = ConsoleAPI::RowCount();
		s_currCols = ConsoleAPI::ColCount();

		// TODO - Maybe resize console after clearing it to avoid console resize error
		ConsoleAPI::SetConsoleSize(s_currRows, s_currCols);

		ConsoleAPI::ClearConsole();

		PrintHeader();
		PrintContent();
		PrintFooter();

		s_guitest->Print();
	}
};
int ConsoleManager::s_currRows = 0;
int ConsoleManager::s_currCols = 0;
std::shared_ptr<Panel> ConsoleManager::s_guitest;
TextColor ConsoleManager::_defaultColor = { BLACK, WHITE };
TextColor ConsoleManager::_headerColor = { WHITE, BLACK };
TextColor ConsoleManager::_contentColor = { BLACK, WHITE };
TextColor ConsoleManager::_footerColor = { WHITE, BLACK };

}