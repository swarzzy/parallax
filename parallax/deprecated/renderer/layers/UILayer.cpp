//#include <renderer/layers/UILayer.h>
//#include "renderer/BatchRenderer2D.h"
//
//#include <hypermath.h>
//#include "shading/Shader.h"
//#include "renderer/renderable/UI/UIClickable.h"
//
//namespace prx {
//	UILayer::UILayer()
//		: Layer(new BatchRenderer2D,
//				new Shader("res/shaders/UI_shader.vs", "res/shaders/UI_shader.fs"),
//				hpm::mat4::ortho(0.0, Window::getCurrentWindow().getWidth(), 
//									Window::getCurrentWindow().getHeight(), 0.0, -10.0, 10.0)) {}
//
//	UILayer::~UILayer() {
//		delete m_Shader;
//		for (auto widget : m_Widgets)
//			delete widget;
//	}
//
//	void UILayer::add(Renderable2D* renderable) {
//		if (UIWidget* widget = dynamic_cast<UIWidget*>(renderable))
//			m_Widgets.push_back(widget);
//		else
//			m_Renderables.push_back(renderable);
//	}
//
//	void UILayer::update() {
//		for (auto& widget : m_Widgets)
//			widget->update();
//	}
//
//	void UILayer::draw() {
//		m_Shader->bind();
//
//		m_Renderer->begin();
//		
//		for (auto renderable : m_Renderables)
//			renderable->submit(m_Renderer);
//
//		for (auto widget : m_Widgets)
//			widget->submit(m_Renderer);
//
//		m_Renderer->end();
//
//		m_Renderer->flush();
//
//		m_Shader->unbind();
//	}
//
//	void UILayer::updateProjectionMatrix() {
//		auto mtx = hpm::mat4::ortho(0.0, Window::getCurrentWindow().getWidth(),
//									Window::getCurrentWindow().getHeight(), 0.0, -10.0, 10.0);
//		setProjectionMatrix(mtx);
//	}
//}
