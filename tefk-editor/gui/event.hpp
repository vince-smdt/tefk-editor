#pragma once
#include "types.h"

namespace tefk {

struct Event {
	enum class Type {
		APPLICATION_START,
		CHARACTER,
		CONSOLE_SIZE_CHANGE,
		SPECIAL_CHARACTER,
		TIMER_UP,
		WINDOW_CLOSING
	};

	TefkChar input;
	Type type;

	static Event ApplicationStart();
	static Event Character(TefkChar input);
	static Event ConsoleSizeChange();
	static Event SpecialCharacter(TefkChar input);
	static Event TimerUp();
	static Event WindowClosing();
};

} // namespace tefk