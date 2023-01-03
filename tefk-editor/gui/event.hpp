#pragma once
namespace tefk {

// TODO - maybe make event class a struct
class Event {
public:
	enum class Type {
		CHARACTER,
		SPECIAL_CHARACTER,
		CONSOLE_SIZE_CHANGE
	};

	char input;
	Type type;

	static Event Character(char input);
	static Event SpecialCharacter(char input);
	static Event ConsoleSizeChange();
};

}