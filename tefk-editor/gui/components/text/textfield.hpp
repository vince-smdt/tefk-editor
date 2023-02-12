#pragma once
#include "text.hpp"

namespace tefk {

class TextField : public Text {
	TefkString _label;
public:
	TextField();

	TefkString GetLabel();
	void SetLabel(TefkString label);

	TefkString GetContent() override;
	bool CatchEventFromBaseComponent(Event event) override;
private:
	void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk