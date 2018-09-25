#include <renderer/renderable/UI/UIButtonBase.h>
#include <resources/Resources.h>
#include <renderer/Renderer2D.h>
#include <Fonts/Font.h>
#include <event/UI/OnClickListener.h>

namespace prx {
	UIButtonBase::UIButtonBase(hpm::vec3 position, hpm::vec2 size, std::string_view text, Font* font, Texture* texPressed, Texture* texReleased)
				 : UIClickable(position, size, texReleased, false),
				   m_Label(text),
				   m_Font(font),
				   m_PressedTex(texPressed),
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

	void UIButtonBase::submit(Renderer2D* renderer) const {
		renderer->submit(*this);
		renderer->drawString(m_Label, hpm::vec3(m_LblPosX, m_LblPosY, m_Position.z + 0.1), m_Font, 0xffffffff);
	}

	void UIButtonBase::pressed(bool pressed) {
		if (m_Pressed != pressed && pressed == false) {
			m_Pressed = false;
			m_Texture = m_ReleasedTex;
		} 
		else if (m_Pressed != pressed && pressed == true) {
			m_Pressed = true;
			m_Texture = m_PressedTex;
		}
	}

	void UIButtonBase::setOnClickListener(event::OnClickListener& listener) {
		m_OnClickListener = &listener;
	}

	void UIButtonBase::onClick() {
		pressed(true);
		if (m_OnClickListener != nullptr)
			m_OnClickListener->onClick(this);
	}

	void UIButtonBase::onRelease() {
		pressed(false);
		if (m_OnClickListener != nullptr)
			m_OnClickListener->onRelease(this);
	}
}
