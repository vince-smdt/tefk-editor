#include "consoleapi.hpp"

namespace tefk {

HANDLE ConsoleAPI::s_handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO ConsoleAPI::s_csbi;
Coord ConsoleAPI::s_lastRecordedSize = { 0, 0 };

void ConsoleAPI::Init() {
    // Disable Ctrl+C closing app
    SetConsoleCtrlHandler(NULL, TRUE);

    DWORD prevOutputMode;
    DWORD prevInputMode;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hOutput, &prevOutputMode);
    GetConsoleMode(hInput, &prevInputMode);

    // Activate Virtual Terminal Sequences
    prevOutputMode |= ENABLE_PROCESSED_OUTPUT
                   |  ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Disable quick edit mode
    prevInputMode = ENABLE_EXTENDED_FLAGS | (prevInputMode & ~ENABLE_QUICK_EDIT_MODE);

    SetConsoleMode(hInput, prevOutputMode);
    SetConsoleMode(hInput, prevInputMode);
}

bool ConsoleAPI::ConsoleSizeChanged() {
    return s_lastRecordedSize != ConsoleAPI::GetConsoleSize();
}

Coord ConsoleAPI::GetConsoleSize() {
    GetConsoleBufferInfo();
    return Coord(
        s_csbi.srWindow.Right - s_csbi.srWindow.Left + 1,
        s_csbi.srWindow.Bottom - s_csbi.srWindow.Top + 1
    );
}

void ConsoleAPI::UpdateConsoleSize() {
    s_lastRecordedSize = ConsoleAPI::GetConsoleSize();
    COORD currSize = { s_lastRecordedSize.X, s_lastRecordedSize.Y };

    if (!SetConsoleScreenBufferSize(s_handle, currSize)) {
        DWORD errorCode = GetLastError();
        Logger::Instance().Log(
            Logger::LogLevel::ERR,
            "SetConsoleScreenBufferSize() failed! Reason : {}", 
            errorCode
        );
        exit(0);
    }
}

void ConsoleAPI::GetConsoleBufferInfo() {
    if (!GetConsoleScreenBufferInfo(s_handle, &s_csbi)) {
        DWORD errorCode = GetLastError();
        Logger::Instance().Log(
            Logger::LogLevel::ERR,
            "GetConsoleBufferInfo() failed! Reason : {}", 
            errorCode
        );
        exit(0);
    }
}

} // namespace tefk
