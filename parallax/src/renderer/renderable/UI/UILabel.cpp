#include <renderer/renderable/UI/UILabel.h>
#include <renderer/Renderer2D.h>

namespace prx {

	UILabel::UILabel(std::string_view text, hpm::vec3 position, Font* font, unsigned int color)
		: UIWidget(position, hpm::vec2(0.0), color), m_Text(text), m_Font(font) {}

	void UILabel::submit(Renderer2D* renderer) const {
		renderer->drawString(m_Text, m_Position, m_Font, m_Color);
	}
}
