#pragma once
#ifndef _PARALLAX_RENDERER_UI_BUTTON_H_
#define _PARALLAX_RENDERER_UI_BUTTON_H_
#include "UIWidget.h"
#include <iostream>

namespace prx::event {
	class OnClickListener;
}

namespace prx {
class Font;

	class UIButton : public UIWidget {
	private:
		std::string  m_Label;
		Font*		 m_Font;
		float		 m_LblPosX;
		float		 m_LblPosY;
		TextureBase* m_PressedTex;
		TextureBase* m_ReleasedTex;
		
		event::OnClickListener* m_OnClickListener;
	public:
		UIButton(hpm::vec3 position, float size, std::string_view text);

		void submit(Renderer2D* renderer) const override;

		void pressed(bool pressed);

		void setOnClickListener(event::OnClickListener& listener);

		inline const std::string& getLabel() const { return m_Label; }
	
		void onClick() override;
		void onRelease() override;
	};
}
#endif
