#pragma once
#include "text.hpp"

namespace tefk {

class TextField : public Text {
	TefkString _label;
	std::function<void()> _onSubmit;
public:
	TextField();

	TefkString GetLabel();
	void SetLabel(TefkString label);

	void SetOnSubmit(std::function<void()> func);

	TefkString GetContent() override;
	bool CatchEventFromBaseComponent(Event event) override;
private:
	void GetPixelVector(PixelVector& pixelVec) override;
};

} // namespace tefk