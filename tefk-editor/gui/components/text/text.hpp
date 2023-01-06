#include "../guicomponent.hpp"

namespace tefk {

struct Cursor {
	std::vector<std::string>::iterator row;
	std::string::iterator col;
};

class Text : public GUIComponent {
protected:
	Cursor _cursor;
public:
	Text();
};

} // namespace tefk