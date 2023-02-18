#pragma once
#include "guicomponent.hpp"

namespace tefk {

class Label : public GUIComponent {
	TefkString _text;
public:
	Label();

	// Text
	void SetText(TefkString text);
	TefkString GetContent() override;
private:
	void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk