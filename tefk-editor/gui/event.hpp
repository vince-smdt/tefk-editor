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

	unsigned char input;
	Type type;

	static Event Character(unsigned char input);
	static Event SpecialCharacter(unsigned char input);
	static Event ConsoleSizeChange();
};

}