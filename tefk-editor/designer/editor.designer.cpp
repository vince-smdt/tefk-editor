#include "editor.designer.hpp"

namespace tefk::Designer {

std::shared_ptr<Window> Editor() {
	std::shared_ptr<Window> window = std::make_shared<Window>();

	/**********************************/
	/*             HEADER             */
	/**********************************/
	std::shared_ptr<Panel> panHeader = std::make_shared<Panel>(Coord(0, 0), Coord(0, 1), TextColor(WHITE, BLACK));

	std::shared_ptr<Label> lblHeader = std::make_shared<Label>(Coord(0, 0), Coord(0, 1), TextColor(WHITE, BLACK));
	lblHeader->SetDynamicText([]() -> std::string {
		return Editor::CurrentFile().GetFilename().generic_string() + " " // TODO - Find cleaner way of printing info without having
			+ std::to_string(Editor::FileIndex() + 1) + "/"			  //		to call std::to_string() everytime
			+ std::to_string(Editor::Files().size()) + " "
			+ "Press Ctrl+S to save!";
	});

	/**********************************/
	/*            CONTENT             */
	/**********************************/
	std::shared_ptr<Panel> panEditor = std::make_shared<Panel>(Coord(0, 1), Coord(0, 0), TextColor(BLACK, WHITE));
	panEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 2);
	});

	std::shared_ptr<TextEditor> lblEditor = std::make_shared<TextEditor>(Coord(0, 2), Coord(0, 0), TextColor(BLACK, WHITE));
	lblEditor->SetDynamicHeight([]() -> short {
		return (short)(ConsoleAPI::RowCount() - 3);
	});
	lblEditor->SetDynamicText([]() -> std::string {
		return Editor::CurrentFile().GetContent();
	});

	/**********************************/
	/*             FOOTER             */
	/**********************************/
	std::shared_ptr<Panel> panFooter = std::make_shared<Panel>(Coord(0, 0), Coord(0, 1), TextColor(WHITE, BLACK));
	panFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
	});

	std::shared_ptr<Label> lblFooter = std::make_shared<Label>(Coord(0, 0), Coord(0, 1), TextColor(WHITE, BLACK));
	lblFooter->SetDynamicPosition([]() -> Coord {
		return { 0, (short)(ConsoleAPI::RowCount() - 1) };
	});
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