#pragma once
#ifndef _PARALLAX_RENDERER_UI_BUTTON_BASE_H_
#define _PARALLAX_RENDERER_UI_BUTTON_BASE_H_

#include <iostream>

#include "UIClickable.h"
#include "../../../resources/Resources.h"

namespace prx::event {
	class OnClickListener;
}

namespace prx {
class Font;

	class UIButtonBase : public UIClickable {
	protected:
		std::string  m_Label;
		Font*		 m_Font;
		float		 m_LblPosX;
		float		 m_LblPosY;
		TextureBase* m_PressedTex;
		TextureBase* m_ReleasedTex;
		
		event::OnClickListener* m_OnClickListener;

		UIButtonBase(const hpm::vec2& position, 
					 const hpm::vec2& size,
					 std::string_view text,
					 Font* font,
					 Texture* texPressed,
					 Texture* texReleased);

	public:
		virtual ~UIButtonBase() {};

		void submit(Renderer2D* renderer) const override;

		void pressed(bool pressed);

		void setOnClickListener(event::OnClickListener& listener);

		inline const std::string& getLabel() const { return m_Label; }
	
		void onClick() override;
		void onRelease() override;
	};
}
#endif
