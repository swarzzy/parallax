#pragma once
#ifndef _PARALLAX_RENDERER_UI_PANEL_H_
#define _PARALLAX_RENDERER_UI_PANEL_H_

#include <vector>

#include "UIClickable.h"
#include "../Sprite.h"

namespace prx {

	class UIPanel;

	class UIPanelMinButton : public UIClickable {
	private:
		UIPanel* m_Panel;

		//void onClick() override;

		UIPanelMinButton(UIPanel* panel, const hpm::vec3& position, const hpm::vec2& size, unsigned int color, bool pressed)
			: UIClickable(position, size, color, pressed), m_Panel(panel) {}
	public:
		friend class UIPanel;
	};

	class UIPanel : public UIClickable {
	protected:
		std::vector<UIWidget*>  m_Widgets;
		Sprite*					m_Background;;
		Sprite*					m_Header;
		UIPanelMinButton*		m_MinButton;
		float					m_FilledSpace;
		bool					m_Minimized;
		hpm::vec2				m_BackgroundSize;
	public:
		UIPanel(const hpm::vec3& position, 
				Texture* background, 
				Texture* head, Texture*, 
				Texture* minButton,
				bool minimized);

	public:
		virtual ~UIPanel() {};

		//void add(UIWidget* widget);

		void submit(Renderer2D* renderer) const override;
		
		void update() override;

		//void minimize(bool minimize);

		inline bool isMinimized() const { return m_Minimized; }
	};
}
#endif
