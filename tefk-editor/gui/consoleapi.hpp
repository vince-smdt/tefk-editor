#pragma once
#include <conio.h>
#include <Windows.h>

#include "color.hpp"
#include "../logger.hpp" // TODO - maybe move logger inside gui, own folder/projet? (remove gui folder dependency on external file)

namespace tefk {

class ConsoleAPI {
    // TODO - make it so we don't have to delete the contructors, namespace?
    ConsoleAPI() = delete;
    ConsoleAPI(const ConsoleAPI&) = delete;

    static HANDLE s_handle;
    static CONSOLE_SCREEN_BUFFER_INFO s_csbi;
    static TefkCoord s_lastRecordedSize;
public:
    static void Init();

    static bool ConsoleSizeChanged();
    static TefkCoord GetConsoleSize();
    static void UpdateConsoleSize();
private:
    static void GetConsoleBufferInfo();
};

} // namespace tefk
