#pragma once
namespace tefk {

struct Event {
	enum class Type {
		APPLICATION_START,
		CHARACTER,
		CONSOLE_SIZE_CHANGE,
		SPECIAL_CHARACTER,
		WINDOW_CLOSING
	};

	unsigned char input;
	Type type;
	bool focused = false; // If component receiving event is focused

	static Event ApplicationStart();
	static Event Character(unsigned char input);
	static Event ConsoleSizeChange();
	static Event SpecialCharacter(unsigned char input);
	static Event WindowClosing();
};

} // namespace tefk