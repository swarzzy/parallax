#include "Label.h"

namespace prx {
	Label::Label(std::string_view text, hpm::vec3 position, hpm::vec4 color)
		: Renderable2D(position, hpm::vec2(0.0), color), m_Text(text) {}

	void Label::submit(Renderer2D* renderer) const {
		//renderer->drawString(m_Text, m_Position.x, m_Position.y, m_Color);
	}
}
