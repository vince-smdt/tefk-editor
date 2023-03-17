#pragma once
#include "../gui/components/label.hpp"
#include "../gui/window.hpp"

namespace tefk {

class Menu : public Window {
    Label _lblHeader;
    Label _lblTemp;
public:
    Menu();

    // Events
    void CatchEvent(Event event) override;
};

} // namespace tefk
