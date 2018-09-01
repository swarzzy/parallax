#pragma once
#ifndef _PARALLAX_GRAPHICS_LABEL_H
#define _PARALLAX_GRAPHICS_LABEL_H

#include "Renderable2D.h"

namespace prx {
	class Label : public Renderable2D {
	private:
		std::string m_Text;
	public:
		Label(std::string_view text, hpm::vec3 position, hpm::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};
}
#endif

