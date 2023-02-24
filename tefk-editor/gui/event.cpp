#include "event.hpp"

namespace tefk {

Event Event::ApplicationStart() {
    Event event;
    event.type = Type::APPLICATION_START;
    return event;
}

Event Event::Character(TefkChar input) {
    Event event;
    event.input = input;
    event.type = Type::CHARACTER;
    return event;
}

Event Event::ConsoleSizeChange() {
    Event event;
    event.type = Type::CONSOLE_SIZE_CHANGE;
    return event;
}

Event Event::SpecialCharacter(TefkChar input) {
    Event event;
    event.input = input;
    event.type = Type::SPECIAL_CHARACTER;
    return event;
}

Event Event::TimerUp() {
    Event event;
    event.type = Type::TIMER_UP;
    return event;
}

Event Event::WindowClosing() {
    Event event;
    event.type = Type::WINDOW_CLOSING;
    return event;
}

} // namespace tefk
