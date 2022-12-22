#include "keypresshandler.hpp"

// TODO - Avoid redundant filecontent string declaration in each function
namespace tefk::KeyPressHandler {

void HandleKeyPress(char ch) {
	// TODO - switch case?
	if (ch == VK_BACK) {
		DeleteChar();
	}
	else if (ch == VK_CTRL_BACKSPACE) {
		DeleteWord();
	}
	else if (ch == VK_RETURN) {
		NewLine();
	}
	else if (ch == VK_CTRL_S) {
		SaveFile();
	}
	else {
		AddChar(ch);
	}
}

void DeleteChar() {
	std::string filecontent = Editor::CurrentFile().GetContent();
	if (filecontent.size()) 
		filecontent.erase(filecontent.size() - 1);
	Editor::CurrentFile().SetContent(filecontent);
}

void DeleteWord() {
	std::string filecontent = Editor::CurrentFile().GetContent();
	// TODO - when cursor implemented, make it so only the part of the string behind current cursor position is modified
	// Trim leading spaces
	std::string trimmed = filecontent.substr(0, filecontent.find_last_not_of(' '));

	// If only word in substring, delete all
	// Else, delete word, leaving the space separating it from the previous word
	std::string::size_type lastspace = trimmed.find_last_of(' ');
	filecontent = lastspace == std::string::npos
		? ""
		: filecontent.substr(0, lastspace + 1);
	Editor::CurrentFile().SetContent(filecontent);
}

void NewLine() {
	std::string filecontent = Editor::CurrentFile().GetContent();
	filecontent += '\n';
	Editor::CurrentFile().SetContent(filecontent);
}

void SaveFile() {
	Editor::CurrentFile().Save();
}

void AddChar(char ch) {
	std::string filecontent = Editor::CurrentFile().GetContent();
	filecontent += ch;
	Editor::CurrentFile().SetContent(filecontent);
}

}