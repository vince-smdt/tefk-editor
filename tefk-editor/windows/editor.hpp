#pragma once
#include <vector>

#include "../file.hpp"
#include "../gui/components/label.hpp"
#include "../gui/components/text/texteditor.hpp"
#include "../gui/components/text/textfield.hpp"
#include "../gui/components/window.hpp"

namespace tefk { 

class Editor : public Window {
public:
	Label _lblHeader;
	TextEditor _ediEditor;
	Label _lblFooter;
private:
	std::vector<File> _files;
	std::vector<File>::iterator _currFile; // TODO - check if _currFile is not null before displaying
public:
	Editor();

	void CatchEvent(Event& event) override; // TODO - maybe make event param const ref

	void UpdateHeader();
	void UpdateFooter();

	void LoadFile();
	void OpenFiles(int filecount, char** filenames);
	void PrevFile();
	void NextFile();

	// Properties
	size_t FileIndex();
};

} // namespace tefk