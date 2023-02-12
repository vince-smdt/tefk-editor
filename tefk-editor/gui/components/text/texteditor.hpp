#pragma once
#include <list>

#include "text.hpp"

namespace tefk {

class TextEditor : public Text {
public:
	TextEditor();

	void SetText(TefkString text);

	TefkString GetContent() override;
	bool CatchEventFromBaseComponent(Event event) override;
private:
	void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk