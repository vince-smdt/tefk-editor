#include "editor.hpp"

namespace tefk {

Editor::Editor() 
	: Window{}
{
	// Configure all components
	_lblHeader.SetColor({ BLACK, WHITE });

	_lblError.SetColor({ LIGHT_WHITE, LIGHT_RED });
	_lblError.SetVisibility(false);

	_ediEditor.SetColor({ WHITE, BLACK });

	_txtFilename.SetColor({ WHITE, LIGHT_BLUE });
	_txtFilename.SetLabel("Choose filename");
	_txtFilename.SetVisibility(false);

	_lblFooter.SetColor({ BLACK, WHITE });

	// Add all components to window
	AddComponent(_lblHeader);
	AddComponent(_lblError);
	AddComponent(_ediEditor);
	AddComponent(_txtFilename);
	AddComponent(_lblFooter);

	Focus(_ediEditor);
}

void Editor::CatchEvent(Event event) {
	// Handle event
	if (event.type == Event::Type::CHARACTER) {
		switch (event.input) {
		case VK_CTRL_Q:
			Close();
			break;
		case VK_CTRL_S:
			SaveFile();
			break;
		case VK_RETURN:
			if (_txtFilename.Focused()) {
				if (_currFile->Open(_folderPath.generic_string() + "\\" + _txtFilename.GetText())) {
					SaveFile();
					_txtFilename.SetVisibility(false);
					Focus(_ediEditor);
				}
				else {
					_lblError.SetText("File cannot be created.");
					_lblError.SetVisibility(true);
				}
			}
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
		(_currFile->IsNewFile())
			? "New File"
			: _currFile->GetFilename().generic_string(),
		FileIndex(),
		_files.size()
	));
}

void Editor::UpdateFooter() {
	_lblFooter.SetText(std::format(
		"Rows = {}, Cols = {}",
		ConsoleAPI::GetConsoleSize().Y,
		ConsoleAPI::GetConsoleSize().X
	));
}

void Editor::SaveFile() {
	if (_currFile->IsNewFile()) {
		_txtFilename.SetVisibility(true);
		Focus(_txtFilename);
	}
	else {
		_currFile->SetContent(_ediEditor.GetContent());
		_currFile->Save();
	}
}

void Editor::LoadFile() {
	_ediEditor.SetText(_currFile->GetContent());
}

void Editor::OpenFiles(int argc, char** argv) {
	// TODO - Give option to user to choose path if not detected, change log level?
	if (argc < 2) {
		std::filesystem::path path = argv[0];
		_folderPath = path.parent_path();
		Logger::Instance().Log(
			Logger::LogLevel::INFO,
			"DirPath not specified in command arguments, using executable directory as folderPath."
		);
	}
	else {
		_folderPath = argv[1];

		// Open files from command arguments
		int failedFileOpens = 0;

		for (int i = 2; i < argc; i++) {
			std::filesystem::path filepath(_folderPath.generic_string() + "\\" + argv[i]);
			_files.push_back(File());
			if (!_files.back().Open(filepath)) {
				failedFileOpens++;
				_files.pop_back();
			}
		}

		// Show error if some files failed to open
		if (failedFileOpens) {
			_lblError.SetText(std::format(
				"Failed to open {} file{}.",
				failedFileOpens,
				(failedFileOpens > 1) ? "s" : ""
			));
			_lblError.SetVisibility(true);
		}
	}

	// If not files open, create new file
	if (_files.size() == 0) {
		_files.push_back(File());
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