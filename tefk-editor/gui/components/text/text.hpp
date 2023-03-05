#pragma once
#include <stack>

#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
protected:
    using TefkCharList = std::list<TefkChar>;
    
    struct Action {
        enum ActionType {
            NONE,
            INSERT_TEXT,
            DELETE_TEXT
        };

        ActionType _actionType;
        TefkSizeT _index;
        TefkString _text;

        Action()
            : _actionType{ NONE }
            , _index{ 0 }
        {}
    };

    class Cursor {
        TefkCharList* _list;
        TefkCharList::iterator _iter;
        TefkSizeT _index;
    public:
        // Constructor
        Cursor(TefkCharList& text);

        // Status
        bool AtListBegin();
        bool AtListEnd();

        // Movement
        void Next();
        void Prev();
        void Move(TefkSizeT offset);
        void MoveToIndex(TefkSizeT index);

        // Getters
        TefkCharList::iterator Iter();
        TefkChar Char();
        TefkSizeT Index();

        // Setters
        void SetText(TefkCharList& text);

        // Actions
        TefkChar Delete();
        TefkChar DeleteFront();
        void Add(TefkChar ch);
    };

    TefkCharList _text;
    std::stack<Action> _actions;
    std::stack<Action> _undoneActions;
    Cursor _cursor;
    TefkSizeT _aimedCursorRowIndex; // TODO - minimize use of this line "_aimedCursorRowIndex = RowIndex();", maybe implement decorators?
public:
    // Constructors
    Text();

    // Setters & Getters
    TefkString GetText();

    // Commands
    void MoveCursorRight(bool adjustAimedCursorRowIndex = true);
    void MoveCursorLeft(bool adjustAimedCursorRowIndex = true);
    void MoveCursorUp();
    void MoveCursorDown();
    void MoveCursorNextWord();
    void MoveCursorPrevWord();
    void MoveCursorStartLine(bool adjustAimedCursorRowIndex = true);
    void MoveCursorEndLine(bool adjustAimedCursorRowIndex = true);
    void MoveCursorNextLine(bool adjustAimedCursorRowIndex = true);
    void MoveCursorPrevLine(bool adjustAimedCursorRowIndex = true);
    void MoveCursorToAimedRowIndex();

    void AddChar(TefkChar ch);
    void NewLine();
    void DeleteChar();
    void DeleteWord();
    void DeleteLine();

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
    TefkSizeT RowIndex();
    TefkString SubstringFromList(TefkCharList::iterator begin, TefkCharList::iterator end);
};

} // namespace tefk
