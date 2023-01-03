#include "event.hpp"

namespace tefk {

Event Event::Character(char input) {
	Event event;
	event.input = input;
	event.type = Type::CHARACTER;
	return event;
}

Event Event::SpecialCharacter(char input) {
	Event event;
	event.input = input;
	event.type = Type::SPECIAL_CHARACTER;
	return event;
}

Event Event::ConsoleSizeChange() {
	Event event;
	event.type = Type::CONSOLE_SIZE_CHANGE;
	return event;
}

}