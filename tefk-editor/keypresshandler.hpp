#pragma once
#include "editor.hpp"

namespace tefk {

class KeyPressHandler {
private :
	KeyPressHandler() = delete;
	KeyPressHandler(const KeyPressHandler&) = delete;
public:
	static void HandleKeyPress(char ch) {
		std::string filecontent = Editor::CurrentFile().GetContent();

		switch (ch) {
		case VK_BACK:
			if (filecontent.size()) filecontent.erase(filecontent.size() - 1);
			break;
		case VK_RETURN:
			filecontent += '\n';
			break;
		case VK_PAUSE: // ctrl + s - TODO - Make macro with better name / implement better shortcut key system
			Editor::CurrentFile().Save();
			break;
		default:
			filecontent += ch;
			break;
		}

		Editor::CurrentFile().SetContent(filecontent);
	}
};

}