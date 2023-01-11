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
	else if (event.type == Event::Type::CONSOLE_SIZE_CHANGE) {
		_lblFooter.SetText(
			"Rows = " + std::to_string(ConsoleAPI::RowCount())
			+ ", Cols = " + std::to_string(ConsoleAPI::ColCount())
		);
	}

	// Update components
	_lblHeader.SetText(
		_currFile->GetFilename().generic_string() + " "   // TODO - Find cleaner way of printing info without having
		+ std::to_string(FileIndex()) + "/"               // to call std::to_string() everytime
		+ std::to_string(_files.size()) + " "
		+ "Press Ctrl+S to save!"
	);
}

void Editor::LoadFile() {
	_ediEditor.SetText(_currFile->GetContent());
}

void Editor::NewFile() { // TODO - rename functions or fuse newfile with openorcreatefiles
	std::filesystem::path filepath("new.txt");
	_files.push_back(File(filepath)); // TODO - prompt user to enter filename
	_currFile = _files.end() - 1;
	LoadFile();
}

void Editor::OpenOrCreateFiles(int filecount, char** filenames) {
	for (int i = 1; i < filecount; i++) {
		std::filesystem::path filepath(filenames[i]);
		_files.push_back(File(filepath));
	}
	_currFile = _files.end() - 1;
	LoadFile();
}

int Editor::FileIndex() {
	return int((_currFile - _files.begin()) + 1);
}

} // namespace tefk