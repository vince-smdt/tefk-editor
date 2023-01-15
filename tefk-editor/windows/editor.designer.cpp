#include "editor.hpp"

namespace tefk {

Editor::Editor() {
	// Configure all components
	_lblHeader.SetColor({ BLACK, WHITE });

	_ediEditor.SetColor({ WHITE, BLACK });

	_txtFilename.SetColor({ WHITE, LIGHT_RED });
	_txtFilename.SetLabel("Choose filename");
	_txtFilename.SetVisible(false);

	_lblFooter.SetColor({ BLACK, WHITE });

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_txtFilename);
	AddComponent(_lblFooter);
}

} // namespace tefk