#pragma once
#include <vector>

#include "../file.hpp"
#include "../gui/components/label.hpp"
#include "../gui/components/text/texteditor.hpp"
#include "../gui/components/text/textfield.hpp"
#include "../gui/components/window.hpp"

namespace tefk { 

class Editor : public Window {
	Label _lblHeader;
	Label _lblError;
	TextEditor _ediEditor;
	TextField _txtFilename;
	Label _lblFooter;

	std::vector<File> _files;
	std::vector<File>::iterator _currFile; // TODO - check if _currFile is not null before displaying
	std::filesystem::path _folderPath;
public:
	Editor();

	// Events
	void CatchEvent(Event event) override;

	// Component updaters
	void UpdateHeader();
	void UpdateFooter();

	// Editor actions
	void SaveFile();
	void LoadFile();
	void OpenFiles(int filecount, char** filenames);
	void PrevFile();
	void NextFile();
	void SetFilename();

	// Properties
	size_t FileIndex();
};

} // namespace tefk