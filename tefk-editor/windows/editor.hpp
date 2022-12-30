#pragma once
#include <vector>
#include "../file.hpp"
#include "../gui/components/label.hpp"
#include "../gui/components/panel.hpp"
#include "../gui/components/texteditor.hpp"
#include "../gui/components/textfield.hpp"
#include "../gui/components/window.hpp"
#include "../keypresshandler.hpp"

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
	std::vector<File>::size_type _file_index;
public:
	Editor();
	static Editor& Instance(); // TODO - Make class instantiable, not a singleton when possible
	
	void Update() override;
	void CatchEvent(Event& event) override; // TODO - maybe make event param const ref

	std::vector<File>& Files();
	File& CurrentFile();
	std::vector<File>::size_type& FileIndex();

	void NewFile();
	void OpenOrCreateFiles(int filecount, char** filenames);
};

}
