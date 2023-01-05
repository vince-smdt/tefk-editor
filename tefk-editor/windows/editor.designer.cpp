#include "editor.hpp"

namespace tefk {

Editor::Editor() {
	// Header
	_lblHeader.SetHeight(1);
	_lblHeader.SetColor({ WHITE, BLACK });

	// Content
	_ediEditor.SetPosition({ 0, 1 });
	_ediEditor.SetColor({ BLACK, WHITE });

	// Footer
	_lblFooter.SetHeight(1);
	_lblFooter.SetColor({ WHITE, BLACK });
	_lblFooter.SetText(
		"Rows = " + std::to_string(ConsoleAPI::RowCount())
		+ ", Cols = " + std::to_string(ConsoleAPI::ColCount())
	);

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_lblFooter);
}

}