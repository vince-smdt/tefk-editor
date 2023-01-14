#include "editor.hpp"

namespace tefk {

void Editor::CatchEvent(Event& event) {
	// Handle event
	if (event.type == Event::Type::CHARACTER) {
		switch (event.input) {
		case VK_CTRL_S:
			_currFile->SetContent(_ediEditor.GetText());
			_currFile->Save();
			break;
		}
	}
	else if (event.type == Event::Type::SPECIAL_CHARACTER) {
		switch (event.input) {
		case VK_PAGE_DOWN:
			NextFile();
			break;
		case VK_PAGE_UP:
			PrevFile();
			break;
		}
	}
	else if (event.type == Event::Type::CONSOLE_SIZE_CHANGE) {
		UpdateFooter();
	}
}

void Editor::UpdateHeader() {
	_lblHeader.SetText(std::format(
		"{} {}/{} Press Ctrl+S to save!",
		_currFile->GetFilename().generic_string(),
		FileIndex(),
		_files.size()
	));
}

void Editor::UpdateFooter() {
	_lblFooter.SetText(std::format(
		"Rows = {}, Cols = {}",
		ConsoleAPI::RowCount(),
		ConsoleAPI::ColCount()
	));
}

void Editor::LoadFile() {
	_ediEditor.SetText(_currFile->GetContent());
}

void Editor::OpenFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		_files.push_back(File(filepath));
	}

	if (_files.size() == 0) {
		std::filesystem::path filepath("new.txt");
		_files.push_back(File(filepath));
	}

	_currFile = _files.begin();
	LoadFile();
	UpdateHeader();
}

void Editor::PrevFile() {
	_currFile->SetContent(_ediEditor.GetText());
	if (_currFile == _files.begin())
		_currFile = _files.end() - 1;
	else
		_currFile--;
	LoadFile();
	UpdateHeader();
}

void Editor::NextFile() {
	_currFile->SetContent(_ediEditor.GetText());
	if (_currFile == _files.end() - 1)
		_currFile = _files.begin();
	else
		_currFile++;
	LoadFile();
	UpdateHeader();
}

size_t Editor::FileIndex() {
	return _currFile - _files.begin() + 1;
}

} // namespace tefk