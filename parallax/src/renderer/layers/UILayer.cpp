#include <renderer/layers/UILayer.h>
#include "renderer/BatchRenderer2D.h"

#include <hypermath.h>
#include "shading/Shader.h"

namespace prx {
	UILayer::UILayer(Window * window)
		: Layer(new BatchRenderer2D,
				new Shader("res/shaders/UI_shader.vs", "res/shaders/UI_shader.fs"),
				hpm::mat4::ortho(0.0, window->getWidth(), window->getHeight(), 0.0, -10.0, 10.0)),
		m_Window(window) {

	}

	UILayer::~UILayer() {
		delete m_Shader;
		for (auto widget : m_Widgets)
			delete widget;
		for (auto widget : m_ClickableWidgets)
			delete widget;
	}

	void UILayer::addWidget(UIWidget* widget) {
		if (widget->isClickable())
			m_ClickableWidgets.push_back(widget);
		else
			m_Widgets.push_back(widget);
	}

	void UILayer::update() {
		mouseTest();
	}

	void UILayer::draw() {
		m_Shader->bind();

		m_Renderer->begin();
		
		for (auto renderable : m_Renderables)
			renderable->submit(m_Renderer);

		for (auto widget : m_Widgets)
			widget->submit(m_Renderer);

		for (auto widget : m_ClickableWidgets)
			widget->submit(m_Renderer);

		m_Renderer->end();

		m_Renderer->flush();

		m_Shader->unbind();
	}

	void UILayer::updateProjectionMatrix() {
		auto mtx = hpm::mat4::ortho(0.0, m_Window->getWidth(),
									m_Window->getHeight(), 0.0, -10.0, 10.0);
		setProjectionMatrix(mtx);
	}

	void UILayer::mouseTest() {
		hpm::vec2 cursorPos = m_Window->getCursorPos();
	
		for (auto& clickable : m_ClickableWidgets) {
			hpm::vec3 pos = clickable->getPosition();
			hpm::vec2 size = clickable->getSize();

			if (
				m_Window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) &&
				(cursorPos.x > pos.x && cursorPos.x < (pos.x + size.x) &&
					cursorPos.y > pos.y && cursorPos.y < (pos.y + size.y))
				) {
				clickable->onClick();
			}
			else if (
					 m_Window->isMouseButtonReleased(GLFW_MOUSE_BUTTON_1) &&
					 clickable->isPressed()
					) {
				clickable->onRelease();
			}
				
		}
	}
}
