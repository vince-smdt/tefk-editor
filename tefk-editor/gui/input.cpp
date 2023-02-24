#include "input.hpp"

namespace tefk::Input {

Event CatchInput() {
    unsigned char c = ConsoleAPI::ReadKeypress();

    if (c == 0 || c == 224) {
        c = ConsoleAPI::ReadKeypress();
        return Event::SpecialCharacter(c);
    }

    return Event::Character(c);
}

} // namespace tefk
