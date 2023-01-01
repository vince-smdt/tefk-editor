#include "editor.hpp"

namespace tefk {

void Editor::Update() {
	_lblHeader.SetText(
		_currFile->GetFilename().generic_string() + " "   // TODO - Find cleaner way of printing info without having
		+ std::to_string(FileIndex()) + "/"               // to call std::to_string() everytime
		+ std::to_string(_files.size()) + " "
		+ "Press Ctrl+S to save!"
	);

	_ediEditor.SetHeight((short)(ConsoleAPI::RowCount() - 2));
	_ediEditor.SetText(_currFile->GetContent());

	_panFooter.SetPosition({ 0, (short)(ConsoleAPI::RowCount() - 1) });

	_lblFooter.SetPosition({ 0, (short)(ConsoleAPI::RowCount() - 1) });
	_lblFooter.SetText(
		"Rows = " + std::to_string(ConsoleAPI::RowCount())
		+ ", Cols = " + std::to_string(ConsoleAPI::ColCount())
	);
}

void Editor::CatchEvent(Event& event) {
	if (event.type == Event::Type::KEYPRESS)
		HandleKeyPress(event.input);
}

void Editor::NewFile() { // TODO - rename functions or fuse newfile with openorcreatefiles
	std::filesystem::path filepath("new.txt");
	_files.push_back(File(filepath)); // TODO - prompt user to enter filename
	_currFile = _files.end() - 1;
}

void Editor::OpenOrCreateFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		_files.push_back(File(filepath));
	}
	_currFile = _files.end() - 1;
}

int Editor::FileIndex() {
	return (int)((_currFile - _files.begin()) + 1);
}

void Editor::HandleKeyPress(char ch) {
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

void Editor::DeleteChar() {
	std::string filecontent = _currFile->GetContent();
	if (filecontent.size())
		filecontent.erase(filecontent.size() - 1);
	_currFile->SetContent(filecontent);
}

void Editor::DeleteWord() {
	std::string filecontent = _currFile->GetContent();
	// TODO - when cursor implemented, make it so only the part of the string behind current cursor position is modified
	// Trim leading spaces
	std::string trimmed = filecontent.substr(0, filecontent.find_last_not_of(' '));

	// If only word in substring, delete all
	// Else, delete word, leaving the space separating it from the previous word
	std::string::size_type lastspace = trimmed.find_last_of(' ');
	filecontent = lastspace == std::string::npos
		? ""
		: filecontent.substr(0, lastspace + 1);
	_currFile->SetContent(filecontent);
}

void Editor::NewLine() {
	std::string filecontent = _currFile->GetContent();
	filecontent += '\n';
	_currFile->SetContent(filecontent);
}

void Editor::SaveFile() {
	_currFile->Save();
}

void Editor::AddChar(char ch) {
	std::string filecontent = _currFile->GetContent();
	filecontent += ch;
	_currFile->SetContent(filecontent);
}

}