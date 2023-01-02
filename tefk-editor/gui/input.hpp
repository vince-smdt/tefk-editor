#pragma once
#include "event.hpp"

#define VK_BACK 0x08
#define VK_RETURN 0x0D
#define VK_CTRL_S 0x13
#define VK_CTRL_BACKSPACE 0x7F

namespace tefk::Input {

Event CatchInput();

}