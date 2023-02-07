#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	TefkString _text;
public:
	Label();

	void SetText(TefkString text);

	TefkString GetContent() override;
private:
	void DrawOnCanvas() override;
};

} // namespace tefk