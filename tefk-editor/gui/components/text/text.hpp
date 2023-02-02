#pragma once
#include <stack>

#include "../guicomponent.hpp"

namespace tefk {

class Text : public GUIComponent {
public:
	using value_type = std::string;
	using char_type = value_type::value_type;
	
	struct Action {
		enum ActionType {
			NONE,
			INSERT_TEXT,
			DELETE_TEXT
		};

		ActionType _actionType;
		long long _movementOffset;
		value_type _text;

		Action() 
			: _actionType{ ActionType::NONE },
			  _movementOffset{ 0 }
		{}

		void Reset() {
			_actionType = ActionType::NONE;
			_movementOffset = 0;
			_text = "";
		}
	};
protected:
	std::list<char_type> _text;
	std::list<char_type>::iterator _cursor;
	std::stack<Action> _actions;
	Action _currAction;
public:
	// Constructors
	Text();

	// Setters & Getters
	value_type GetText();

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

	// Action handler
	void AddEvent();

	// Events
	void CatchEvent(Event event) override;
	virtual bool CatchEventFromBaseComponent(Event event) { return false; }
protected:
	// Helper functions
	size_t SpacesFromLeft();
	value_type SubstringFromList(std::list<char_type>::iterator begin, std::list<char_type>::iterator end);
};

} // namespace tefk