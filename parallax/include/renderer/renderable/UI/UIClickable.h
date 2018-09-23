#pragma once
#ifndef _PARALLAX_RENDERER_UI_CLICKABLE_H_
#define _PARALLAX_RENDERER_UI_CLICKABLE_H_

#include "UIWidget.h"

namespace prx {
	class UIClickable : public UIWidget {
	protected:
		bool m_Pressed;

	protected:
		UIClickable(const hpm::vec3& position, const hpm::vec2& size, unsigned int color, bool pressed)
			: UIWidget(position, size, color), m_Pressed(pressed) {};

		UIClickable(const hpm::vec3& position, const hpm::vec2& size, Texture* texture, bool pressed)
			: UIWidget(position, size, texture), m_Pressed(pressed) {};
	public:
		virtual ~UIClickable() {};

		virtual void update() override;

		virtual void onClick() {};
		virtual void onRelease() {};

		inline bool isPressed() const { return m_Pressed; }
	};
}

#endif
