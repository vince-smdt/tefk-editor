#pragma once
#include <list>

#include "text.hpp"

namespace tefk {

class TextEditor : public Text {
public:
	TextEditor();

	void SetText(std::string text);
	std::string GetText();

	void CatchEvent(Event& event) override;
private:
	void DrawOnCanvas() override;
};

} // namespace tefk