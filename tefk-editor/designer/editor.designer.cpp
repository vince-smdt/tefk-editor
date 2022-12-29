#include "../editor.hpp"

namespace tefk {

Editor::Editor() {
	/**********************************/
	/*             HEADER             */
	/**********************************/
	_panHeader = std::make_shared<Panel>();
	_panHeader->SetHeight(1);
	_panHeader->SetColor({ WHITE, BLACK });

	_lblHeader = std::make_shared<Label>();
	_lblHeader->SetHeight(1);
	_lblHeader->SetColor({ WHITE, BLACK });

	/**********************************/
	/*            CONTENT             */
	/**********************************/
	_ediEditor = std::make_shared<TextEditor>();
	_ediEditor->SetPosition({ 0, 1 });
	_ediEditor->SetColor({ BLACK, WHITE });

	/**********************************/
	/*             FOOTER             */
	/**********************************/
	_panFooter = std::make_shared<Panel>();
	_panFooter->SetHeight(1);
	_panFooter->SetColor({ WHITE, BLACK });

	_lblFooter = std::make_shared<Label>();
	_lblFooter->SetHeight(1);
	_lblFooter->SetColor({ WHITE, BLACK });

	// Add all components to window
	AddComponent(_panHeader);
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_panFooter);
	AddComponent(_lblFooter);
}

}