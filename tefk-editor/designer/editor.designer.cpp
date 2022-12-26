#include "editor.designer.hpp"

namespace tefk::Designer {

std::shared_ptr<Window> Editor() {
	std::shared_ptr<Window> window = std::make_shared<Window>();

	/**********************************/
	/*             HEADER             */
	/**********************************/
	std::shared_ptr<Panel> panHeader = std::make_shared<Panel>();
	panHeader->SetColor({ WHITE, BLACK });
	panHeader->SetHeight(1);

	std::shared_ptr<Label> lblHeader = std::make_shared<Label>();
	lblHeader->SetColor({ WHITE, BLACK });
	lblHeader->SetHeight(1);
	lblHeader->SetDynamicText([]() -> std::string {
		return Editor::CurrentFile().GetFilename().generic_string() + " " // TODO - Find cleaner way of printing info without having
			+ std::to_string(Editor::FileIndex() + 1) + "/"			  //		to call std::to_string() everytime
			+ std::to_string(Editor::Files().size()) + " "
			+ "Press Ctrl+S to save!";
	});

	/**********************************/
	/*            CONTENT             */
	/**********************************/
	std::shared_ptr<Panel> panEditor = std::make_shared<Panel>();
	panEditor->SetColor({ BLACK, WHITE });
	panEditor->SetPosition({ 0, 1 });
	panEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 2);
	});

	// TODO - Maybe use text field here instead
	std::shared_ptr<Label> lblEditor = std::make_shared<Label>();
	lblEditor->SetColor({ BLACK, WHITE });
	lblEditor->SetPosition({ 0, 2 });
	lblEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 3);
	});
	lblEditor->SetDynamicText([]() -> std::string {
		return Editor::CurrentFile().GetContent();
	});

	/**********************************/
	/*             FOOTER             */
	/**********************************/
	std::shared_ptr<Panel> panFooter = std::make_shared<Panel>();
	panFooter->SetColor({ WHITE, BLACK });
	panFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
	});
	panFooter->SetHeight(1);

	std::shared_ptr<Label> lblFooter = std::make_shared<Label>();
	lblFooter->SetColor({ WHITE, BLACK });
	lblFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
	});
	lblFooter->SetHeight(1);
	lblFooter->SetDynamicText([]() -> std::string {
		return "Rows = " + std::to_string(ConsoleAPI::RowCount())
			+ ", Cols = " + std::to_string(ConsoleAPI::ColCount());
	});

	window->AddComponent(panHeader);
	window->AddComponent(lblHeader);
	window->AddComponent(panEditor);
	window->AddComponent(lblEditor);
	window->AddComponent(panFooter);
	window->AddComponent(lblFooter);

	return window;
}

}