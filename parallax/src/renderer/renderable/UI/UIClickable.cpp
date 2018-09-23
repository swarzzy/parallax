#include <renderer/renderable/UI/UIClickable.h>

#include <window/Window.h>

namespace prx {
	void UIClickable::update() {
		hpm::vec2 cursorPos = Window::getCurrentWindow().getCursorPos();
			if (
				Window::getCurrentWindow().isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) &&
				(cursorPos.x > m_Position.x && cursorPos.x < (m_Position.x + m_Size.x) &&
					cursorPos.y > m_Position.y && cursorPos.y < (m_Position.y + m_Size.y))
			   ) 
				onClick(); 
			else if (
				Window::getCurrentWindow().isMouseButtonReleased(GLFW_MOUSE_BUTTON_1) && m_Pressed)
				onRelease();
	}
}