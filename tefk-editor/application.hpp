#pragma once
#include <conio.h>
#include <memory>
#include <queue>
#include <stack>

#include "gui/canvas.hpp"
#include "gui/window.hpp"
#include "gui/input.hpp"

namespace tefk {

// Forward declarations
class Window;

// TODO - change class name to Application, isn't a manager but just an app
class Application {
    bool _running;
    std::stack<Window*> _windows;
    std::queue<std::shared_ptr<Event>> _events;
    Canvas _canvas;
public:
    Application();

    // Canvas
    Canvas& GetCanvas();

    // Window
    void OpenWindow(Window& window);
    void CloseWindow();

    // Events
    void CatchEvents();
    void AddEvent(Event event);
    void RunEvents();
    void ProcessEvent(Event event);

    // Actions
    void Render();
    bool Running();
    void CloseApp();
};

} // namespace tefk
