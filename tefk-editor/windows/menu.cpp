#include "menu.hpp"

namespace tefk {

Menu::Menu()
    : Window{}
{ 
    // Configure all components
    _lblHeader.SetText("Selection menu");
    _lblHeader.SetColor({ LIGHT_WHITE, LIGHT_BLUE });

    _lblTemp.SetText("In construction, press Esc to return to editor!");
    _lblTemp.SetSizeBehaviour(SizeBehaviour::FILL);
    _lblTemp.SetColor({ LIGHT_WHITE, LIGHT_RED });

    // Add all components to window
    AddComponent(_lblHeader);
    AddComponent(_lblTemp);
}

void Menu::CatchEvent(Event event) {
    // Handle event
    if (event.type == Event::Type::CHARACTER) {
        switch (event.input) {
        case KC_ESC:
            Close();
            break;
        }
    }
}

} // namespace tefk
