#pragma once
#ifndef _PARALLAX_RENDERER_UI_WIDGET_H_
#define _PARALLAX_RENDERER_UI_WIDGET_H_

#include "../Renderable2D.h"
#include "../../textures/Texture.h"

namespace prx {
	class Window;

	class UIWidget : public Renderable2D {
	private:
		inline static unsigned int m_GlobalWidgetCounter = 0;

	protected:	
		unsigned int m_ID;

	protected:
		UIWidget()
			: Renderable2D(),
				m_ID(m_GlobalWidgetCounter) {
			m_GlobalWidgetCounter++;
		}

		UIWidget(const hpm::vec3& position, const hpm::vec2& size, unsigned int color, bool storeTransformCache = false)
			: Renderable2D(position, size, color, storeTransformCache),
				m_ID(m_GlobalWidgetCounter) {
			m_GlobalWidgetCounter++;
		};

		UIWidget(hpm::vec3 position, hpm::vec2 size, Texture* texture, bool storeTransformCache = false)
			: Renderable2D(position, size, texture, storeTransformCache),
				m_ID(m_GlobalWidgetCounter) {
			m_GlobalWidgetCounter++;
		};

	public:
		virtual ~UIWidget() {};

		virtual void update() = 0;

		inline unsigned int getID() const { return m_ID; }
	};
}
#endif
