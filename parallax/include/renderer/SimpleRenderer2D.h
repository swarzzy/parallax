#pragma once
#ifndef _SIMPLERENDERER2D_H_
#define _SIMPLERENDERER2D_H_

#ifdef PARALLAX_USE_DEPRECATED_FEATURES

#include <deque>

#include "Renderer2D.h"
#include "renderable/StaticSprite.h"

namespace prx {
	class SimpleRenderer2D : public Renderer2D {

	private:
		std::deque<const StaticSprite*> m_RendererQueue;
	public:
		SimpleRenderer2D();
		
		void submit(const Renderable2D& renderable) override;
		void flush() override;
	};
}
#endif
#endif