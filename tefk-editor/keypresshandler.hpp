#pragma once
#include "editor.hpp"

#define VK_BACK 0x08
#define VK_RETURN 0x0D
#define VK_CTRL_S 0x13
#define VK_CTRL_BACKSPACE 0x7F

namespace tefk::KeyPressHandler {
	void HandleKeyPress(char ch);

	// Delete
	void DeleteChar();
	void DeleteWord();

	// New line
	void NewLine();
	
	// File
	void SaveFile();

	// Write
	void AddChar(char ch);
}