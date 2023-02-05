#pragma once
#include <stack>

#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
protected:
	using string_type = std::string;
	using size_type = string_type::size_type;
	using char_type = string_type::value_type;
	using list_type = std::list<char_type>;
	
	struct Action {
		enum ActionType {
			NONE,
			INSERT_TEXT,
			DELETE_TEXT
		};

		ActionType _actionType;
		size_type _index;
		string_type _text;
	};

	class Cursor {
		list_type* _list;
		list_type::iterator _iter;
		size_type _index;
	public:
		// Constructor
		Cursor(list_type& text);

		// Status
		bool AtListBegin();
		bool AtListEnd();

		// Movement
		void Next();
		void Prev();
		void Move(size_type offset);
		void MoveToIndex(size_type index);

		// Getters
		list_type::iterator Iter();
		char_type Char();
		size_type Index();

		// Setters
		// TODO - Remove this method after optimization
		void SetText(list_type& text);
		void Iter(list_type::iterator iter);

		// Actions
		char Delete();
		void Add(char_type ch);
	};

	list_type _text;
	std::stack<Action> _actions;
	std::stack<Action> _undoneActions;
	Cursor _cursor;
public:
	// Constructors
	Text();

	// Setters & Getters
	string_type GetText();

	// Commands
	void MoveCursorRight();
	void MoveCursorLeft();
	void MoveCursorUp();
	void MoveCursorDown();
	void MoveCursorNextWord();
	void MoveCursorPrevWord();

	void AddChar(char_type ch);
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
	string_type SubstringFromList(list_type::iterator begin, list_type::iterator end);
};

} // namespace tefk