#include "input.hpp"

namespace tefk::Input {

Event CatchInput() {
	// TODO - Change _getch() for function that can properly read Fn keys
	// TODO - Change _getch() for function that can read letters with accents (Ex. �, �, �, �, ...)
	return Event::Character(_getch());
}

}