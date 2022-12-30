#pragma once
namespace tefk {

// TODO - maybe make event class a struct
class Event {
public:
	enum class Type {
		KEYPRESS,
		CONSOLE_SIZE_CHANGE
	};

	char input;
	Type type;

	static Event Keypress(char input);
	static Event ConsoleSizeChange();
};

}