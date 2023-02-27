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
    _txtFilename.SetOnSubmit(std::bind(&Editor::SetFilename, this));

    _lblFooter.SetColor({ BLACK, WHITE });

    // Add all components to window
    AddComponent(_lblHeader);
    AddComponent(_lblError);
    AddComponent(_ediEditor);
    AddComponent(_txtFilename);
    AddComponent(_lblFooter);

    // Bound timers to methods
    AddTimerBoundProcedure(&_timerError, std::bind(&Editor::HideError, this));

    // Focus on text editor panel
    Focus(_ediEditor);
}

void Editor::CatchEvent(Event event) {
    // Handle event
    if (event.type == Event::Type::CHARACTER) {
        switch (event.input) {
        case VK_CTRL_D:
            RemoveFile();
            break;
        case VK_CTRL_N:
            NewFile();
            break;
        case VK_CTRL_Q:
            Close();
            break;
        case VK_CTRL_S:
            SaveFile();
            break;
        case VK_ESC:
            OpenMenu();
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

    // Update components
    UpdateHeader();
    UpdateFooter();
}

void Editor::UpdateHeader() {
    _lblHeader.SetText(std::format(
        "{} {}/{} Ctrl+S to save! Esc for menu!",
        (_currFile->IsNewFile())
            ? "New File"
            : _currFile->GetFilename().generic_string(),
        FileIndex(),
        _files.size()
    ));
}

void Editor::UpdateFooter() {
    Coord size = ConsoleAPI::GetConsoleSize();
    _lblFooter.SetText(std::format(
        "Rows = {}, Cols = {}",
        size.Y,
        size.X
    ));
}

void Editor::SaveFile() {
    if (_currFile->IsNewFile()) {
        _txtFilename.SetVisibility(true);
        Focus(_txtFilename);
        return;
    }
    _currFile->SetContent(_ediEditor.GetContent());
    _currFile->Save();
}

void Editor::LoadFile() {
    _ediEditor.SetText(_currFile->GetContent());
}

void Editor::OpenFiles(int argc, char** argv) {
    // If directory or file not specified in command line arguments
    if (argc < 2) {
        std::filesystem::path executablePath = argv[0];
        _folderPath = executablePath.parent_path();
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
            RaiseError(std::format(
                "Failed to open {} file{}.",
                failedFileOpens,
                (failedFileOpens > 1) ? "s" : ""
            ));
        }
    }

    // If not files open, create new file
    if (_files.size() == 0) {
        _files.push_back(File());
    }

    _currFile = _files.begin();
    LoadFile();
}

void Editor::PrevFile() {
    _currFile->SetContent(_ediEditor.GetContent());
    if (_currFile == _files.begin())
        _currFile = _files.end() - 1;
    else
        _currFile--;
    LoadFile();
}

void Editor::NextFile() {
    _currFile->SetContent(_ediEditor.GetContent());
    if (_currFile == _files.end() - 1)
        _currFile = _files.begin();
    else
        _currFile++;
    LoadFile();
}

void Editor::NewFile() {
    _currFile->SetContent(_ediEditor.GetContent());
    _files.push_back(File());
    _currFile = _files.end() - 1;
    LoadFile();
}

void Editor::RemoveFile() {
    if (_files.size() == 1) {
        _files.clear();
        _files.push_back(File());
        _currFile = _files.begin();
        LoadFile();
        return;
    }
    _currFile = _files.erase(_currFile);
    if (_currFile == _files.end())
        _currFile--;
    LoadFile();
}

void Editor::SetFilename() {
    if (_currFile->Open(_folderPath.generic_string() + "\\" + _txtFilename.GetText())) {
        SaveFile();
        _txtFilename.SetVisibility(false);
        Focus(_ediEditor);
        UpdateHeader();
        return;
    }
    RaiseError("File cannot be created.");
}

void Editor::OpenMenu() {
    GetParent().OpenWindow(_menuWindow);
}

void Editor::RaiseError(TefkString text) {
    _lblError.SetText(text);
    _lblError.SetVisibility(true);
    _timerError.StartTimer(5000);
}

void Editor::HideError() {
    _lblError.SetVisibility(false);
}

size_t Editor::FileIndex() {
    return _currFile - _files.begin() + 1;
}

} // namespace tefk
