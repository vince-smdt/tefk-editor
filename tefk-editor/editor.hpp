#pragma once
#include <vector>
#include "file.hpp"
#include "gui/components/label.hpp"
#include "gui/components/panel.hpp"
#include "gui/components/texteditor.hpp"
#include "gui/components/textfield.hpp"
#include "gui/components/window.hpp"

namespace tefk { 

class Editor : public Window {
public:
	std::shared_ptr<Panel> _panHeader;
	std::shared_ptr<Label> _lblHeader;
	std::shared_ptr<Panel> _panEditor;
	std::shared_ptr<TextEditor> _ediEditor;
	std::shared_ptr<Panel> _panFooter;
	std::shared_ptr<Label> _lblFooter;
private:
	std::vector<File> _files;
	std::vector<File>::size_type _file_index;
public:
	Editor();
	static Editor& Instance(); // TODO - Make class instantiable, not a singleton when possible

	std::vector<File>& Files();
	File& CurrentFile();
	std::vector<File>::size_type& FileIndex();

	void NewFile();
	void OpenOrCreateFiles(int filecount, char** filenames);
};

}

