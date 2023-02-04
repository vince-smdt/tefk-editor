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

		Action() 
			: _actionType{ ActionType::NONE },
			  _index{ 0 }
		{}
	};

	class Cursor {
		list_type* _list;
		list_type::iterator _iter;
		size_type _index;
	public:
		Cursor(list_type& text)
			: _list{ &text },
			  _iter { text.begin() },
			  _index { 0 }
		{}

		void SetText(list_type& text) {
			_list = &text;
			_iter = text.begin();
			_index = 0;
		}

		bool AtListBegin() {
			return _iter == _list->begin();
		}

		bool AtListEnd() {
			return _iter == _list->end();
		}

		void Next() {
			if (AtListEnd())
				return;

			_iter++;
			_index++;
		}

		void Prev() {
			if (AtListBegin())
				return;

			_iter--;
			_index--;
		}

		list_type::iterator Iter() {
			return _iter;
		}

		// TODO - Remove this method after optimization
		void Iter(list_type::iterator iter) {
			_iter = iter;
		}

		char_type Char() {
			return *_iter;
		}

		size_type Index() {
			return _index;
		}

		void Move(size_type offset) {
			std::advance(_iter, offset);
			_index += offset;
		}

		void MoveToIndex(size_type index) {
			// Cast to a signed type to allow negative offset
			std::advance(_iter, static_cast<long long>(index - _index));
			_index = index;
		}

		char Delete() {
			if (AtListBegin())
				return '\0';

			char deletedChar = *--_iter;
			_iter = _list->erase(_iter);
			_index--;
			return deletedChar;
		}

		void Add(char_type ch) {
			_list->insert(_iter, ch);
			_index++;
		}
	};

	list_type _text;
	std::stack<Action> _actions;
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

	// Action handler
	void AddAction(Action action);

	// Events
	void CatchEvent(Event event) override;
	virtual bool CatchEventFromBaseComponent(Event event) { return false; }
protected:
	// Helper functions
	size_t SpacesFromLeft();
	string_type SubstringFromList(list_type::iterator begin, list_type::iterator end);
};

} // namespace tefk