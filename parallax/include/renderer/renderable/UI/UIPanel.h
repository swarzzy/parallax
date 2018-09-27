//#pragma once
//#ifndef _PARALLAX_RENDERER_UI_PANEL_H_
//#define _PARALLAX_RENDERER_UI_PANEL_H_
//
//#include <vector>
//
//#include "UIWidget.h"
//#include "../Sprite.h" 
//#include "UIClickable.h"
//#include "../../Renderer2D.h"
//
//namespace prx {
//	
//	class UIPanel;
//
//	class UIPanelHeader : public UIClickable {
//	private:
//		UIPanelHeader(const hpm::vec3& position, const hpm::vec2& size)
//			: UIClickable(position, size, 0xff00ff00, false){
//		}
//	public:
//		friend class UIPanel;
//	};
//
//	class UIPanelButton : public UIClickable {
//	private:
//		UIPanelButton(const hpm::vec3& position, const hpm::vec2& size)
//			: UIClickable(position, size, 0xffff0000, false) {
//		}
//	public:
//		friend class UIPanel;
//	};
//
//	class UIPanel : public UIWidget {
//	private:
//		Sprite* m_Background;
//		UIPanelHeader* m_Header;
//		UIPanelButton* m_MinButton;
//
//		std::vector<UIWidget*> m_Widgets;
//
//	public:
//		UIPanel(const hpm::vec3& position)
//			: UIWidget(position, hpm::vec2(80.0, 34.0), 0xffffffff),
//			m_Background(new Sprite(hpm::vec3(position.x, position.y +  30.0f, position.z), hpm::vec2(80.0, 4.0), 0xff0000ff)),
//			m_Header(new UIPanelHeader(position, hpm::vec2(80.0, 30.0))),
//			m_MinButton(new UIPanelButton(hpm::vec3(position.x + 5.0, position.y + 5.0, position.z), hpm::vec2(20.0))) 
//		{}
//
//		void update() override {}
//
//		void submit(Renderer2D* renderer) const override {
//			renderer->submit(*m_Background);
//			renderer->submit(*m_Header);
//			renderer->submit(*m_MinButton);
//		}
//
//		void add(UIWidget* widget) {
//			m_Widgets.push_back(widget);
//
//			widget->getPosition(hpm::vec3(m_Position.x + 3.0, m_Position )
//
//		}
//		
//	};
//
//	
//}
//
//#endif
