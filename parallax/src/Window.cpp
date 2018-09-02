
#include "window.h"
#include <iostream>
#include "utils/log/Log.h"
#include "utils/GLErrorHandler.h"

namespace prx {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	Window::Window(std::string_view title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height), m_ClearColor(hpm::vec3(0.0, 0.0, 0.0)),
		m_ScrollOffsetX(0), m_ScrollOffsetY(0) {
		if (!init())
			glfwTerminate();
	}


	bool Window::init() {
		if (!glfwInit()) {
			prx::Log::message("Failed to init GLFW", prx::LOG_ERROR);
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			glfwTerminate();
			prx::Log::message("Failed to create window", prx::LOG_ERROR);
			return false;
		}
		glfwMakeContextCurrent(m_Window);

		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSwapInterval(0.0);

		glfwSetWindowUserPointer(m_Window, this);

		if (glewInit() != GLEW_OK) {
			prx::Log::message("Failed to initialize GLEW", prx::LOG_ERROR);
			glfwTerminate();
			return false;
		}

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		return true;
	}
	Window::~Window() {
		glfwTerminate();
	}

	bool Window::isClosed() const {
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::isKeyPressed(unsigned key) const {
		if (key >= MAX_KEYS) {
			prx::Log::message("Invalid key number", prx::LOG_WARNING);
			return false;
		}
		return m_Keys[key];
	}

	bool Window::isMouseButtonPressed(unsigned button) const {
		if (button >= MAX_MOUSE_BUTTONS) {
			prx::Log::message("Invalid mouse button number", prx::LOG_WARNING);
			return false;
		}
		return m_MouseButtons[button];
	}

	void Window::setClearColor(const hpm::vec3& color) {
		glClearColor(color.r, color.g, color.b, 1.0);
	}

	void Window::update() const {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::clear(unsigned int flags) const {
		if (flags & COLOR_BUFFER)
			glClear(GL_COLOR_BUFFER_BIT);
		if (flags & DEPTH_BUFFER)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (key >= 0 && key < MAX_KEYS) {
			if (action == GLFW_PRESS)
				win->m_Keys[key] = true;
			else if (action == GLFW_RELEASE)
				win->m_Keys[key] = false;
		}
		else {
			prx::Log::message("Invalid key number", prx::LOG_WARNING);
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_CursorX = xpos;
		win->m_CursorY = ypos;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (button >= 0 && button < MAX_MOUSE_BUTTONS) {
			if (action == GLFW_PRESS)
				win->m_MouseButtons[button] = true;
			else if (action == GLFW_RELEASE)
				win->m_MouseButtons[button] = false;
		}
		else {
			prx::Log::message("Invalid mouse key number", prx::LOG_WARNING);
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_ScrollOffsetX += xoffset;
		win->m_ScrollOffsetY += yoffset;
	}
}

