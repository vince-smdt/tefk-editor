#include "editor.hpp"

namespace tefk {

Editor::Editor() {
	// Header
	_lblHeader.SetColor({ BLACK, WHITE });

	// Content
	_ediEditor.SetColor({ WHITE, BLACK });

	// Footer
	_lblFooter.SetColor({ BLACK, WHITE });
	_lblFooter.SetText(
		"Rows = " + std::to_string(ConsoleAPI::RowCount())
		+ ", Cols = " + std::to_string(ConsoleAPI::ColCount())
	);

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_lblFooter);
}

} // namespace tefk