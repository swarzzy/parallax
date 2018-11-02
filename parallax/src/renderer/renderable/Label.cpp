#include "Label.h"
#include "../Renderer2D.h"
#include "../../Fonts/FontManager.h"

namespace prx {
	Label::Label(std::string_view text, const Font* font,  unsigned int color)
		: Renderable2D(0.0f, 0.0f, color), m_Text(text), m_Font(font) {}

	Label::Label(std::string_view text, unsigned color)
		: Renderable2D(0.0f, 0.0f, color), m_Text(text), m_Font(FontManager::getInstance()->getDefault()) {}

	void Label::submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) {
		renderer->drawString(m_Text, worldMatrix, depth, m_Font, m_Color);
	}
}
