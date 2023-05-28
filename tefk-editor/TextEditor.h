#pragma once
#include <list>
#include <stack>
#include <vector>

namespace tefk {

// TextEditor types
typedef int ChType;

class TextEditor
{
public:
    TextEditor();

    void SetText(std::vector<ChType> text);
    std::vector<ChType> GetText();

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

    void AddChar(ChType ch);
    void NewLine();
    void DeleteChar();
    void DeleteWord();
    void DeleteLine();

    void Undo();
    void Redo();
private:
    struct Action
    {
        enum ActionType
        {
            NONE,
            INSERT_TEXT,
            DELETE_TEXT
        };

        Action()
            : _actionType(NONE)
            , _index(0)
        {}

        ActionType _actionType;
        size_t _index;
        std::vector<ChType> _text;
    };

    class Cursor
    {
    public:
        // Constructor
        Cursor(std::list<ChType>& text);

        // Status
        bool AtListBegin();
        bool AtListEnd();

        // Movement
        void Next();
        void Prev();
        void Move(size_t offset);
        void MoveToIndex(size_t index);

        // Getters
        std::list<ChType>::iterator Iter();
        ChType Char();
        size_t Index();

        // Setters
        void SetText(std::list<ChType>& text);

        // Actions
        ChType Delete();
        ChType DeleteFront();
        void Add(ChType ch);
    private:
        std::list<ChType> *_list;
        std::list<ChType>::iterator _iter;
        size_t _index;
    };

    std::list<ChType> _text;
    std::stack<Action> _actions;
    std::stack<Action> _undoneActions;
    Cursor _cursor;
    size_t _aimedCursorRowIndex; // TODO - minimize use of this line "_aimedCursorRowIndex = RowIndex();", maybe implement decorators?

private:
    // Action handler
    void AddAction(Action action);
    void ExecuteAction(std::stack<Action>& takeStack, std::stack<Action>& dumpStack);

    // Helper functions
    size_t RowIndex();
    std::vector<ChType> SubstringFromList(std::list<ChType>::iterator begin, std::list<ChType>::iterator end); // TODO - pass vector by ref and change its contents instead of returning copy
};

} // namespace tefk
