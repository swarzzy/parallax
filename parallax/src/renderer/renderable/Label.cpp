#include "Label.h"

namespace prx {
	Label::Label(std::string_view text, hpm::vec2 position, hpm::vec4 color) 
		: Renderable2D(hpm::vec3(position, 0.0), hpm::vec2(0.0), color), m_Text(text) {
	}

	void Label::submit(Renderer2D* renderer) const {
		//renderer->drawString(m_Text, m_Position, m_Color);
	}
}
