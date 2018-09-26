#include <renderer/renderable/UI/UIPanel.h>
#include <renderer/Renderer2D.h>
#include "utils/color/ColorFormatConverter.h"
#include <iostream>

namespace prx {

	//void UIPanelMinButton::onClick() {
	//	if (m_Panel->isMinimized())
	//		m_Panel->minimize(false);
	//	else {
	//		m_Panel->minimize(true);
	//		
	//	}

	//}

	UIPanel::UIPanel(const hpm::vec3 & position, Texture * background, Texture * head, Texture *, Texture * minButton, bool minimized)
		: UIClickable(position, hpm::vec2(20.0f, 22.0f), 0xffffffff, false),
		m_Background(new Sprite(position, hpm::vec2(300.0f, 20.0f), 0xffffffff)),
		m_Header(new Sprite(hpm::vec3(position.x, position.y + 2, position.z), hpm::vec2(20.0f), ColorFormatConverter::rgb(255, 0, 0))),
		m_MinButton(new UIPanelMinButton(this, hpm::vec3(position), hpm::vec2(10), ColorFormatConverter::rgb(0, 255, 0), false)),
		m_FilledSpace(20.0f),
		m_Minimized(minimized) {

	}

	/*void UIPanel::add(UIWidget* widget) {
		m_Widgets.push_back(widget);
		m_Position.y -= widget->getSize().y;
		m_Background->setPosition(hpm::vec3(m_Background->getPosition().x, m_Background->getPosition().y - widget->getSize().y, m_Background->getPosition().z));
		widget->setPosition(hpm::vec3(m_Position.x + 5.0f, m_Position.y + 5.0f, m_Position.z + 0.1f));
		m_FilledSpace += widget->getSize().y;
		m_Size.x = widget->getSize().x + 10.0f;
		m_Background->setSize(hpm::vec2(widget->getSize().x + 10.0f, m_FilledSpace));
		m_Size.y = m_FilledSpace;

		m_Header->setSize(hpm::vec2(m_Size.x, 20.0f));
	}*/

	void UIPanel::submit(Renderer2D* renderer) const {
		renderer->submit(*m_Background);
		//renderer->submit(*m_Header);
		//renderer->submit(*m_MinButton);
		//if (!m_Minimized) {
		//	for (auto& widget : m_Widgets)
		//		renderer->submit(*widget);
		//}
	}

	void UIPanel::update() {
		m_MinButton->update();
		if (!m_Minimized) {
			for (auto& widget : m_Widgets)
				widget->update();
		}
	}

	/*void UIPanel::minimize(bool minimize) {
		if (minimize && !m_Minimized) {
			m_Minimized = true;

			m_ = hpm::vec3(m_Position.x, m_Position.y + m_Size.y - 22, m_Position.z);
		}
		else if (!minimize && m_Minimized)
			m_Minimized = false;


	}
}*/
}