#pragma once
#ifndef _PARALLAX_GRAPHICS_LABEL_H
#define _PARALLAX_GRAPHICS_LABEL_H

#include "Renderable2D.h"
#include "../../Fonts/Font.h"

namespace prx {
	class Label : public Renderable2D {
	private:
		std::string m_Text;
		Font&		m_Font;
	public:
		Label(std::string_view text, hpm::vec3 position, Font& font,  hpm::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};
}
#endif

