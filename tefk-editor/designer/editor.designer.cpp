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
	_lblHeader->SetDynamicText([]() -> std::string {
		return Editor::Instance().CurrentFile().GetFilename().generic_string() + " " // TODO - Find cleaner way of printing info without having
		+ std::to_string(Editor::Instance().FileIndex() + 1) + "/"	         //        to call std::to_string() everytime
		+ std::to_string(Editor::Instance().Files().size()) + " "
		+ "Press Ctrl+S to save!";
		});

	/**********************************/
	/*            CONTENT             */
	/**********************************/
	_panEditor = std::make_shared<Panel>();
	_panEditor->SetPosition({ 0, 1 });
	_panEditor->SetColor({ BLACK, WHITE });
	_panEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 2);
		});

	_ediEditor = std::make_shared<TextEditor>();
	_ediEditor->SetPosition({ 0, 2 });
	_ediEditor->SetColor({ BLACK, WHITE });
	_ediEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 3);
		});
	_ediEditor->SetDynamicText([]() -> std::string {
		return Editor::Instance().CurrentFile().GetContent();
		});

	/**********************************/
	/*             FOOTER             */
	/**********************************/
	_panFooter = std::make_shared<Panel>();
	_panFooter->SetHeight(1);
	_panFooter->SetColor({ WHITE, BLACK });
	_panFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
		});

	_lblFooter = std::make_shared<Label>();
	_lblFooter->SetHeight(1);
	_lblFooter->SetColor({ WHITE, BLACK });
	_lblFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
		});
	_lblFooter->SetDynamicText([]() -> std::string {
		return "Rows = " + std::to_string(ConsoleAPI::RowCount())
		+ ", Cols = " + std::to_string(ConsoleAPI::ColCount());
		});

	AddComponent(_panHeader);
	AddComponent(_lblHeader);
	AddComponent(_panEditor);
	AddComponent(_ediEditor);
	AddComponent(_panFooter);
	AddComponent(_lblFooter);
}

}