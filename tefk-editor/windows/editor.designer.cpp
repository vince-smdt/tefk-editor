#include "editor.hpp"

namespace tefk {

Editor::Editor() {
	// Header
	_lblHeader.SetColor({ BLACK, WHITE });

	// Content
	_ediEditor.SetColor({ WHITE, BLACK });

	// Footer
	_lblFooter.SetColor({ BLACK, WHITE });

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_lblFooter);
}

} // namespace tefk