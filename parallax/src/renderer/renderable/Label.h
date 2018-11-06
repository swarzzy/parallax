#pragma once
#ifndef _PARALLAX_GRAPHICS_LABEL_H
#define _PARALLAX_GRAPHICS_LABEL_H

#include "Renderable2D.h"
#include "../../Fonts/Font.h"

namespace prx {
	class Label : public Renderable2D {
		PRX_DISALLOW_COPY_AND_MOVE(Label)
	protected:
		std::string	m_Text;
		const Font*	m_Font;
	public:
		Label(std::string_view text, const Font* font, unsigned int color = 0xffffffff);
		Label(std::string_view text, unsigned int color = 0xffffffff);

		inline void setText(std::string_view text) noexcept;
		inline void setFont(const Font* font) noexcept;

		inline std::string_view getText() const { return m_Text; }

		void submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) override;
	};

	inline void Label::setText(std::string_view text) noexcept {
		m_Text = text;
	}

	inline void Label::setFont(const Font* font) noexcept {
		m_Font = font;
	}
}
#endif

