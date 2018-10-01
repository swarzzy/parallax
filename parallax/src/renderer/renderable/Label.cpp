#include <renderer/renderable/Label.h>
#include <renderer/Renderer2D.h>

namespace prx {
	Label::Label(std::string_view text, hpm::vec3 position, Font* font,  unsigned int color)
		: Renderable2D(position, hpm::vec2(0.0), color), m_Text(text), m_Font(font) {}

	Label::Label(std::string_view text, float x, float y, float z, Font* font, unsigned color)
		: Renderable2D(hpm::vec3(x, y, z), hpm::vec2(0.0), color), m_Text(text), m_Font(font) {}

	Label::Label(std::string_view text, Font* font, unsigned color)
		: Renderable2D(hpm::vec3(0.0f), hpm::vec2(0.0), color), m_Text(text), m_Font(font) {}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(m_Text, m_Position, m_Font, m_Color);
	}
}
