#include "event.hpp"

namespace tefk {

Event Event::Keypress(char input) {
	Event event;
	event.input = input;
	event.type = Type::KEYPRESS;
	return event;
}

Event Event::ConsoleSizeChange() {
	Event event;
	event.type = Type::CONSOLE_SIZE_CHANGE;
	return event;
}

}