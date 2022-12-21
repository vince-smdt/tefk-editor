#pragma once
#include <iostream>
#include <memory>
#include "editor.hpp"
#include "gui-components/window.hpp"
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

	static std::shared_ptr<Window> s_window;

	// TODO - make these constants
	static TextColor _defaultColor;
	static TextColor _headerColor;
	static TextColor _contentColor;
	static TextColor _footerColor;
public:
	static void Init();

	static bool ConsoleSizeChanged();

	static void Print(std::string text, TextColor color);
	static void PrintHeader();
	static void PrintContent();
	static void PrintFooter();
	static std::ostream& FillRow(std::ostream& stream);
	static void RefreshConsole();
};

}