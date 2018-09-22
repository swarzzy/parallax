#pragma once
#ifndef _PARALLAX_RENDERER_UI_WIDGET_H_
#define _PARALLAX_RENDERER_UI_WIDGET_H_
#include "../Renderable2D.h"
#include "../../textures/Texture.h"

namespace prx {
	class UIWidget : public Renderable2D {
	private:
		inline static unsigned int m_GlobalWidgetCounter = 0;

	protected:	
		unsigned int m_ID;

		bool m_Clickable;
		bool m_Pressed;
		
		UIWidget(hpm::vec3 position, hpm::vec2 size, unsigned int color, bool clickable, bool pressed = false)
			: Renderable2D(position, size, color),
				m_ID(m_GlobalWidgetCounter), m_Clickable(clickable), m_Pressed(pressed) {
			m_GlobalWidgetCounter++;
		};

		UIWidget(hpm::vec3 position, hpm::vec2 size, Texture* texture, bool clickable, bool pressed = false)
			: Renderable2D(position, size, texture),
				m_ID(m_GlobalWidgetCounter), m_Clickable(clickable), m_Pressed(pressed) {
			m_GlobalWidgetCounter++;
		};

	public:
		virtual ~UIWidget() {};
		virtual void onClick() {};
		virtual void onRelease() {};

		inline bool isPressed() const { return m_Pressed; }
		
		inline bool isClickable() const { return m_Clickable; };

		inline unsigned int getID() const { return m_ID; }
	};
}
#endif
