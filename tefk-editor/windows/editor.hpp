#pragma once
#include <vector>
#include "../file.hpp"
#include "../gui/components/label.hpp"
#include "../gui/components/panel.hpp"
#include "../gui/components/texteditor.hpp"
#include "../gui/components/textfield.hpp"
#include "../gui/components/window.hpp"

namespace tefk { 

class Editor : public Window {
public:
	Panel _panHeader;
	Label _lblHeader;
	TextEditor _ediEditor;
	Panel _panFooter;
	Label _lblFooter;
private:
	std::vector<File> _files;
	std::vector<File>::iterator _currFile; // TODO - check if _currFile is not null before displaying
public:
	Editor();

	void Update() override;
	void CatchEvent(Event& event) override; // TODO - maybe make event param const ref

	void NewFile();
	void OpenOrCreateFiles(int filecount, char** filenames);

	// Properties
	int FileIndex();
};

}

