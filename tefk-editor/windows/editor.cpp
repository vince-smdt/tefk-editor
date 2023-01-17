#include "editor.hpp"

namespace tefk {

Editor::Editor() {
	// Configure all components
	_lblHeader.SetColor({ BLACK, WHITE });

	_ediEditor.SetColor({ WHITE, BLACK });

	_txtFilename.SetColor({ WHITE, LIGHT_RED });
	_txtFilename.SetLabel("Choose filename");
	_txtFilename.SetVisible(false);

	_lblFooter.SetColor({ BLACK, WHITE });

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_ediEditor);
	AddComponent(_txtFilename);
	AddComponent(_lblFooter);
}

void Editor::CatchEvent(Event& event) {
	// Handle event
	if (event.type == Event::Type::CHARACTER) {
		switch (event.input) {
		case VK_CTRL_S:
			_currFile->SetContent(_ediEditor.GetContent());
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

void Editor::OpenFiles(int argc, char** argv) {
	// TODO - Give option to user to choose path if not detected, change log level?
	if (argc < 2) {
		Logger::Instance().Log(
			Logger::LogLevel::WARN,
			"DirPath not specified in command arguments, closing application."
		);
		exit(0);
	}

	std::string dirpath = argv[1];

	// Open files from command arguments
	for (int i = 2; i < argc; i++) {
		std::filesystem::path filepath(dirpath + "/" + argv[i]);
		_files.push_back(File(filepath));
	}

	// If not files open, create new file
	if (_files.size() == 0) {
		std::filesystem::path filepath("new.txt");
		_files.push_back(File(filepath));
	}

	_currFile = _files.begin();
	LoadFile();
	UpdateHeader();
}

void Editor::PrevFile() {
	_currFile->SetContent(_ediEditor.GetContent());
	if (_currFile == _files.begin())
		_currFile = _files.end() - 1;
	else
		_currFile--;
	LoadFile();
	UpdateHeader();
}

void Editor::NextFile() {
	_currFile->SetContent(_ediEditor.GetContent());
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