#pragma once
#include "consoleapi.hpp"
#include "event.hpp"

#pragma region Characters
#define KC_CTRL_A               0x01
#define KC_CTRL_B               0x02
#define KC_CTRL_C               0x03
#define KC_CTRL_D               0x04
#define KC_CTRL_E               0x05
#define KC_CTRL_F               0x06
#define KC_CTRL_G               0x07
#define KC_CTRL_H               0x08
#define KC_BACKSPACE            0x08    // TODO - make is so ctrl+h and backspace output different keycodes
#define KC_CTRL_I               0x09
#define KC_TAB                  0x09    // TODO - make is so ctrl+i and tab output different keycodes
#define KC_CTRL_J               0x0A
#define KC_CTRL_K               0x0B
#define KC_CTRL_L               0x0C
#define KC_CTRL_M               0x0D
#define KC_ENTER                0x0D    // TODO - make is so ctrl+m and return output different keycodes
#define KC_CTRL_N               0x0E
#define KC_CTRL_O               0x0F
#define KC_CTRL_P               0x10
#define KC_CTRL_Q               0x11
#define KC_CTRL_R               0x12
#define KC_CTRL_S               0x13
#define KC_CTRL_T               0x14
#define KC_CTRL_U               0x15
#define KC_CTRL_V               0x16
#define KC_CTRL_W               0x17
#define KC_CTRL_X               0x18
#define KC_CTRL_Y               0x19
#define KC_CTRL_Z               0x1A
#define KC_ESC                  0x1B
#define KC_CTRL_BACKSPACE       0x7F
#pragma endregion Characters

#pragma region SpecialCharacters
#define KC_ARROW_UP             0x48
#define KC_PAGE_UP              0x49
#define KC_ARROW_LEFT           0x4B
#define KC_ARROW_RIGHT          0x4D
#define KC_ARROW_DOWN           0x50
#define KC_PAGE_DOWN            0x51
#define KC_CTRL_ARROW_LEFT      0x73
#define KC_CTRL_ARROW_RIGHT     0x74
#pragma endregion SpecialCharacters

namespace tefk {

Event CatchInput();

} // namespace tefk
