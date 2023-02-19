#pragma once
#include "consoleapi.hpp"
#include "event.hpp"

#define VK_ARROW_DOWN          0x50
#define VK_ARROW_LEFT          0x4B
#define VK_ARROW_RIGHT         0x4D
#define VK_ARROW_UP            0x48
#define VK_BACK                0x08
#define VK_CTRL_ARROW_LEFT     0x73
#define VK_CTRL_ARROW_RIGHT    0x74
#define VK_CTRL_BACKSPACE      0x7F
#define VK_CTRL_D              0x04
#define VK_CTRL_N              0x0E
#define VK_CTRL_Q              0x11
#define VK_CTRL_S              0x13
#define VK_CTRL_Y              0x19
#define VK_CTRL_Z			   0x1A
#define VK_PAGE_DOWN           0x51
#define VK_PAGE_UP             0x49
#define VK_RETURN              0x0D

namespace tefk::Input {

Event CatchInput();

} // namespace tefk