#pragma once
#include "editor.hpp"

// TODO - move these macros somewhere else or make it so we don't need macros
#define VK_CTRL_S 0x13
#define VK_CTRL_BACKSPACE 0x7F

namespace tefk {

class KeyPressHandler {
private :
	KeyPressHandler() = delete;
	KeyPressHandler(const KeyPressHandler&) = delete;
public:
	static void HandleKeyPress(char ch) {
		std::string filecontent = Editor::CurrentFile().GetContent();

		// TODO - implement better shortcut key system without if/else if/else conditions
		if (ch == VK_BACK) {
			if (filecontent.size()) filecontent.erase(filecontent.size() - 1);
		}
		else if (ch == VK_RETURN) {
			filecontent += '\n';
		}
		else if (ch == VK_CTRL_S) {
			Editor::CurrentFile().Save();
		}
		else if (ch == VK_CTRL_BACKSPACE) {
			// TODO - when cursor implemented, make it so only the part of the string behind current cursor position is modified
			// Trim leading spaces
			std::string trimmed = filecontent.substr(0, filecontent.find_last_not_of(' '));

			// If only word in substring, delete all
			// Else, delete word, leaving the space separating it from the previous word
			std::string::size_type lastspace = trimmed.find_last_of(' ');
			filecontent = lastspace == std::string::npos
				? ""
				: filecontent.substr(0, lastspace + 1);
		}
		else {
			filecontent += ch;
		}

		Editor::CurrentFile().SetContent(filecontent);
	}
};

}