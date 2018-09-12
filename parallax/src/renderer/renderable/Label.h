#pragma once
#ifndef _PARALLAX_GRAPHICS_LABEL_H
#define _PARALLAX_GRAPHICS_LABEL_H

#include "Renderable2D.h"
#include "../../Fonts/Font.h"

namespace prx {
	class Label : public Renderable2D {
	protected:
		std::string				m_Text;
		std::shared_ptr<Font>	m_Font;
	public:
		Label(std::string_view text, hpm::vec3 position, std::shared_ptr<Font> font, unsigned int color);

		inline void setText(std::string_view text) { m_Text = text; }

		inline std::string_view getText() const { return m_Text; }

		void submit(Renderer2D* renderer) const override;
	};
}
#endif

