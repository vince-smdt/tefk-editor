#pragma once
#include <Windows.h>

namespace tefk {

class KeyPressHandler {
private :
	KeyPressHandler() = delete;
	KeyPressHandler(const KeyPressHandler&) = delete;
public:
	static void handleKeyPress(char ch, std::string& filecontent) {
		switch (ch) {
		case VK_BACK:
			if (filecontent.size()) filecontent.erase(filecontent.size() - 1);
			break;
		case VK_RETURN:
			filecontent += '\n';
			break;
		default:
			filecontent += ch;
			break;
		}
	}
};

}