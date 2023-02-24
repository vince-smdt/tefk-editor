#pragma once
#include <stack>

#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
protected:
    using list_type = std::list<TefkChar>;
    
    struct Action {
        enum ActionType {
            NONE,
            INSERT_TEXT,
            DELETE_TEXT
        };

        ActionType _actionType;
        TefkSizeT _index;
        TefkString _text;
    };

    class Cursor {
        list_type* _list;
        list_type::iterator _iter;
        TefkSizeT _index;
    public:
        // Constructor
        Cursor(list_type& text);

        // Status
        bool AtListBegin();
        bool AtListEnd();

        // Movement
        void Next();
        void Prev();
        void Move(TefkSizeT offset);
        void MoveToIndex(TefkSizeT index);

        // Getters
        list_type::iterator Iter();
        TefkChar Char();
        TefkSizeT Index();

        // Setters
        void SetText(list_type& text);

        // Actions
        TefkChar Delete();
        TefkChar DeleteFront();
        void Add(TefkChar ch);
    };

    list_type _text;
    std::stack<Action> _actions;
    std::stack<Action> _undoneActions;
    Cursor _cursor;
public:
    // Constructors
    Text();

    // Setters & Getters
    TefkString GetText();

    // Commands
    void MoveCursorRight();
    void MoveCursorLeft();
    void MoveCursorUp();
    void MoveCursorDown();
    void MoveCursorNextWord();
    void MoveCursorPrevWord();

    void AddChar(TefkChar ch);
    void NewLine();
    void DeleteChar();
    void DeleteWord();

    void Undo();
    void Redo();

    // Events
    void CatchEvent(Event event) override;
    virtual bool CatchEventFromBaseComponent(Event event) { return false; }
protected:
    // Action handler
    void AddAction(Action action);
    void ExecuteAction(std::stack<Action>& takeStack, std::stack<Action>& dumpStack);

    // Helper functions
    size_t SpacesFromLeft();
    TefkString SubstringFromList(list_type::iterator begin, list_type::iterator end);
};

} // namespace tefk
