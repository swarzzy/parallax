#include "Label.h"
#include "../Renderer2D.h"

namespace prx {
	Label::Label(std::string_view text, hpm::vec3 position, const Font& font,  unsigned int color)
		: Renderable2D(position, hpm::vec2(0.0), color), m_Text(text), m_Font(font) {}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(m_Text, m_Position, m_Font, m_Color);
	}
}
