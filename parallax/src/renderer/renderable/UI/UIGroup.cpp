//#include <renderer/renderable/UI/UIGroup.h>
//
//#include "renderer/Renderer2D.h"
//#include "renderer/renderable/UI/UIClickable.h"
//
//#include <window/Window.h>
//
//namespace prx {
//	UIGroup::UIGroup(const hpm::mat4 & transformation) 
//		: m_TransformationMatrix(transformation) {}
//
//	UIGroup::~UIGroup() {
//		for (auto* widget : m_Widgets)
//			delete widget;
//	}
//
//	void UIGroup::add(UIWidget* widget) {
//		m_Widgets.push_back(widget);
//	}
//
//	void UIGroup::submit(Renderer2D* renderer) const {
//		renderer->push(m_TransformationMatrix);
//
//		for (auto widget : m_Widgets) {
//			widget->update();
//			widget->submit(renderer);
//		}
//
//		renderer->pop();
//	}
//
//	void UIGroup::update() {
//		for (auto widget : m_Widgets) {
//			widget->update();
//		}
//	}
//
//}
