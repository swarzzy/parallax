#pragma once
#ifndef _PARALLAX_RENDERER_UI_LABEL_H_
#define _PARALLAX_RENDERER_UI_LABEL_H_
#include "UIWidget.h"
#include "../../../Fonts/Font.h"

namespace prx {
	// Same as Label actually
	class UILabel : public UIWidget {
	protected:
		std::string	m_Text;
		Font*		m_Font;
	public:
		UILabel(std::string_view text, hpm::vec3 position, Font* font, unsigned int color);

		inline void setText(std::string_view text) { m_Text = text; }

		inline std::string_view getText() const { return m_Text; }

		void submit(Renderer2D* renderer) const override;

		void update() override {};
	};
}
#endif
