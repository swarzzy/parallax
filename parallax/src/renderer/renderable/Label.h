#pragma once
#ifndef _PARALLAX_RENDERABLE_LABEL_H_
#define _PARALLAX_RENDERABLE_LABEL_H_

#include "Renderable2D.h"

namespace prx {
	class Label : public Renderable2D {
	private:
		std::string m_Text;
	public:
		Label(std::string_view text, hpm::vec2 position, hpm::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};
}
#endif

