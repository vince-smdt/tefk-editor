#include "designer.hpp"

namespace tefk::Designer {

std::shared_ptr<Window> Editor() {
	std::shared_ptr<Window> window = std::make_shared<Window>();

	std::shared_ptr<Panel> pan = std::make_shared<Panel>();
	pan->SetDynamicSize([pan]() -> Coord {
		return { (short)(ConsoleAPI::ColCount() - 5 - pan.get()->GetPosition().X), 4 };
		});
	pan->SetColor({ BLUE, WHITE });
	pan->SetDynamicPosition([]() -> Coord {
		if (ConsoleAPI::ColCount() > 75)
		return { 40, 20 };
		else
			return { 40, 30 };
		});

	std::shared_ptr<Label> lbl = std::make_shared<Label>();
	lbl->SetDynamicSize([lbl]() -> Coord {
		return { (short)(ConsoleAPI::ColCount() - 5 - lbl.get()->GetPosition().X), 2 };
		});
	lbl->SetColor({ BLUE, LIGHT_GREEN });
	lbl->SetPosition({ 40, 20 });
	lbl->SetDynamicText([]() -> std::string {
		return "This is a test label, there are "
		+ std::to_string(ConsoleAPI::RowCount()) +
		" rows and "
		+ std::to_string(ConsoleAPI::ColCount()) +
		" columns.";
		});

	std::shared_ptr<TextField> txt = std::make_shared<TextField>();
	txt->SetDynamicSize([txt]() -> Coord {
		return { (short)(ConsoleAPI::ColCount() - 5 - txt.get()->GetPosition().X), 2 };
		});
	txt->SetDynamicColor([]() -> TextColor {
		if (ConsoleAPI::ColCount() > 75)
		return { BLUE, LIGHT_YELLOW };
		else
			return { BLUE, LIGHT_RED };
		});
	txt->SetPosition({ 40, 22 });
	txt->AddText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbccc");

	window->AddComponent(pan);
	window->AddComponent(lbl);
	window->AddComponent(txt);

	return window;
}

}