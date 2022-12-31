#include "editor.hpp"

namespace tefk {

void Editor::Update() {
	_lblHeader.SetText(
		_files[_fileIndex].GetFilename().generic_string() + " " // TODO - Find cleaner way of printing info without having
		+ std::to_string(_fileIndex + 1) + "/"	           //        to call std::to_string() everytime
		+ std::to_string(_files.size()) + " "
		+ "Press Ctrl+S to save!"
	);

	_ediEditor.SetHeight((short)(ConsoleAPI::RowCount() - 2));
	_ediEditor.SetText(_files[_fileIndex].GetContent());

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
	_fileIndex = _files.size() - 1;
}

void Editor::OpenOrCreateFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		_files.push_back(File(filepath));
	}
	_fileIndex = _files.size() - (filecount + 1);
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
	std::string filecontent = _files[_fileIndex].GetContent();
	if (filecontent.size())
		filecontent.erase(filecontent.size() - 1);
	_files[_fileIndex].SetContent(filecontent);
}

void Editor::DeleteWord() {
	std::string filecontent = _files[_fileIndex].GetContent();
	// TODO - when cursor implemented, make it so only the part of the string behind current cursor position is modified
	// Trim leading spaces
	std::string trimmed = filecontent.substr(0, filecontent.find_last_not_of(' '));

	// If only word in substring, delete all
	// Else, delete word, leaving the space separating it from the previous word
	std::string::size_type lastspace = trimmed.find_last_of(' ');
	filecontent = lastspace == std::string::npos
		? ""
		: filecontent.substr(0, lastspace + 1);
	_files[_fileIndex].SetContent(filecontent);
}

void Editor::NewLine() {
	std::string filecontent = _files[_fileIndex].GetContent();
	filecontent += '\n';
	_files[_fileIndex].SetContent(filecontent);
}

void Editor::SaveFile() {
	_files[_fileIndex].Save();
}

void Editor::AddChar(char ch) {
	std::string filecontent = _files[_fileIndex].GetContent();
	filecontent += ch;
	_files[_fileIndex].SetContent(filecontent);
}

}