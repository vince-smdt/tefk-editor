#include "input.hpp"

namespace tefk {

Event CatchInput() {
    unsigned char c = _getch();

    if (c == 0 || c == 224) {
        c = _getch();
        return Event::SpecialCharacter(c);
    }

    return Event::Character(c);
}

} // namespace tefk
