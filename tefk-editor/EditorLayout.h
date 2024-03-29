//#pragma once
//#include <vector>
//
//#include "../File.h"
//
//namespace tefk { 
//
//class Editor
//{
//    Label _lblHeader;
//    Label _lblError;
//    TextEditor _ediEditor;
//    TextField _txtFilename;
//    Label _lblFooter;
//
//    Timer _timerError;
//
//    Menu _menuWindow;
//
//    std::vector<File> _files;
//    std::vector<File>::iterator _currFile; // TODO - check if _currFile is not null before displaying
//    std::filesystem::path _folderPath;
//public:
//    Editor();
//
//    // Events
//    void CatchEvent(Event event) override;
//
//    // Component updaters
//    void UpdateHeader();
//    void UpdateFooter();
//
//    // Editor actions
//    void SaveFile();
//    void LoadFile();
//    void OpenFiles(int filecount, char** filenames);
//    void PrevFile();
//    void NextFile();
//    void NewFile();
//    void RemoveFile();
//    void SetFilename();
//
//    // Menu
//    void OpenMenu();
//
//    // Helper functions
//    void RaiseError(TefkString text);
//    void HideError();
//
//    // Properties
//    size_t FileIndex();
//};
//
//} // namespace tefk
