#include <renderer/renderable/UI/UIButton.h>
#include <resources/Resources.h>
#include <renderer/Renderer2D.h>
#include <Fonts/Font.h>
#include <event/UI/OnClickListener.h>

namespace prx {
	UIButton::UIButton(hpm::vec3 position, float size, std::string_view text)
		: UIWidget(position,
				 hpm::vec2(size, size * 0.4),
				 Resources::getTexture(Resources::loadTexture("res/textures/button_released.png")),
				 true),
		  m_Label(text),
		  m_Font(Resources::getFont(RESOURCES_DEFAULT_FONT_ID)),
		  m_PressedTex(Resources::getTexture(Resources::loadTexture("res/textures/button_pressed.png"))),
		  m_ReleasedTex(m_Texture),
		  m_OnClickListener(nullptr) {
		
		// Calculating label position on button
		float lblSizeX = 0.0;
		float lblSizeY = 0.0;

		for (auto ch : m_Label) {
			auto chars = m_Font->getCharacters();
			auto glyph = chars[ch];
			float rBearing = (glyph.Advance >> 6) - glyph.Size.x - glyph.Bearing.x;
			lblSizeX += (glyph.Size.x + glyph.Bearing.x + rBearing) * m_Font->getScale();
			if (glyph.Size.y > lblSizeY)
				lblSizeY = glyph.Size.y;
		}
		lblSizeY *= m_Font->getScale();

		// Multiply by 2.1 because of some weird bug with font
		m_LblPosX = (m_Position.x + (m_Size.x / 2)) - (lblSizeX / 2.1);
		m_LblPosY = (m_Position.y + (m_Size.y / 2)) - (lblSizeY / 2.1);
		
	}

	void UIButton::submit(Renderer2D* renderer) const {
		renderer->submit(*this);
		renderer->drawString(m_Label, hpm::vec3(m_LblPosX, m_LblPosY, m_Position.z + 0.1), m_Font, 0xffffffff);
	}

	void UIButton::pressed(bool pressed) {
		if (m_Pressed != pressed && pressed == false) {
			m_Pressed = false;
			m_Texture = m_ReleasedTex;
		} 
		else if (m_Pressed != pressed && pressed == true) {
			m_Pressed = true;
			m_Texture = m_PressedTex;
		}
	}

	void UIButton::setOnClickListener(event::OnClickListener& listener) {
		m_OnClickListener = &listener;
	}

	void UIButton::onClick() {
		pressed(true);
		if (m_OnClickListener != nullptr)
			m_OnClickListener->onClick(this);
	}

	void UIButton::onRelease() {
		pressed(false);
		if (m_OnClickListener != nullptr)
			m_OnClickListener->onRelease(this);
	}
}
