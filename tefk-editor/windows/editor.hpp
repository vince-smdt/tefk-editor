#pragma once
#include <vector>
#include "../file.hpp"
#include "../gui/components/label.hpp"
#include "../gui/components/panel.hpp"
#include "../gui/components/texteditor.hpp"
#include "../gui/components/textfield.hpp"
#include "../gui/components/window.hpp"

#define VK_BACK 0x08
#define VK_RETURN 0x0D
#define VK_CTRL_S 0x13
#define VK_CTRL_BACKSPACE 0x7F

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
	std::vector<File>::size_type _fileIndex;
public:
	Editor();

	void Update() override;
	void CatchEvent(Event& event) override; // TODO - maybe make event param const ref

	void NewFile();
	void OpenOrCreateFiles(int filecount, char** filenames);

	// Handle input
	// TODO - clean this up later, make easier to read or move to another file
	void HandleKeyPress(char ch);
	void DeleteChar();
	void DeleteWord();
	void NewLine();
	void SaveFile();
	void AddChar(char ch);
};

}

