#include "window.hpp"

namespace tefk {

Window::Window()
    : _parentApp{ nullptr }
    , _focusedComponent { nullptr }
    , _isClosing{ false }
{}

void Window::SetParent(ApplicationManager& parentApp) {
    _parentApp = &parentApp;
}

ApplicationManager& Window::GetParent() {
    return *_parentApp;
}

void Window::AddComponent(GUIComponent& component) {
    // TODO - check if component already has a parent
    _children.push_back(&component);
    component.SetParent(*this);
}

// TODO - avoid giving negative values to components height
void Window::UpdateComponents() {
    // Select visible components
    std::list<GUIComponent*> visibleComponents;

    for (auto component : _children)
        if (component->IsVisible())
            visibleComponents.push_back(component);

    // Update component properties

    // WIDTH
    for (auto component : visibleComponents)
        component->SetWidth(ConsoleAPI::GetConsoleSize().X);

    // HEIGHT
    TefkCoordSizeT availableSpace = ConsoleAPI::GetConsoleSize().Y;
    std::list<GUIComponent*> fillComponents;

    // Update content height components
    // Store pointers of fill height components
    for (auto component : visibleComponents) {
        // TODO - update height in separate function (maybe do same for width)
        switch (component->GetSizeBehaviour()) {
        case SizeBehaviour::CONTENT: {
            TefkSizeT contentSize = component->GetContent().size();
            TefkSizeT divider = component->GetWidth() == 0 ? contentSize : component->GetWidth();

            component->SetHeight((TefkCoordSizeT)ceil(double(contentSize) / divider));
            availableSpace -= component->GetHeight();
            break;
        }
        case SizeBehaviour::FILL:
            fillComponents.push_back(component);
            break;
        }
    }

    // Update height of fill height components
    if (fillComponents.size() > 0) {
        TefkCoordSizeT fillHeight = availableSpace / TefkCoordSizeT(fillComponents.size());
        TefkCoordSizeT leftoverSpace = availableSpace % fillComponents.size();
        for (auto component : fillComponents) {
            if (component != fillComponents.back())
                component->SetHeight(fillHeight);
            else
                component->SetHeight(fillHeight + leftoverSpace);
        }
    }

    // Position every component vertically
    TefkCoordSizeT offsetY = 0;
    for (auto component : visibleComponents) {
        component->SetPosition({ 0, offsetY });
        offsetY += component->GetHeight();
    }
}

void Window::AddTimerBoundProcedure(Timer* timer, std::function<void()> procedure) {
    _timerBoundProcedures.push_back(std::pair(timer, procedure));
}

void Window::Render() {
    GetCanvas().Resize(ConsoleAPI::GetConsoleSize().X, ConsoleAPI::GetConsoleSize().Y);
    for (auto& child : _children)
        if (child->IsVisible())
            child->DrawOnCanvas();
    GetCanvas().Render();
}

void Window::Focus(GUIComponent& component) {
    _focusedComponent = &component;
}

void Window::Open() {
    _isClosing = false;
}

void Window::Close() {
    _isClosing = true;
}

GUIComponent& Window::GetFocusedComponent() {
    return *_focusedComponent;
}

bool Window::IsClosing() {
    return _isClosing;
}

bool Window::ExecuteTimerBoundProcedures() {
    bool proceduresExecuted = false;

    for (auto& timerBoundProcedure : _timerBoundProcedures) {
        if (timerBoundProcedure.first->Ringing()) {
            timerBoundProcedure.second();
            timerBoundProcedure.first->StopTimer();
            proceduresExecuted = true;
        }
    }

    return proceduresExecuted;
}

Canvas& Window::GetCanvas() {
    return _parentApp->GetCanvas();
}

void Window::CatchAndPropagateEvent(Event event) {
    CatchEvent(event);
    for (auto& child : _children)
        child->CatchEvent(event);
}

} // namespace tefk
