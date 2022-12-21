#pragma once
#include "editor.hpp"

// TODO - move these macros somewhere else or make it so we don't need macros
#define VK_BACK 0x08
#define VK_RETURN 0x0D
#define VK_CTRL_S 0x13
#define VK_CTRL_BACKSPACE 0x7F

namespace tefk {

class KeyPressHandler {
private :
	KeyPressHandler() = delete;
	KeyPressHandler(const KeyPressHandler&) = delete;
public:
	static void HandleKeyPress(char ch);
};

}