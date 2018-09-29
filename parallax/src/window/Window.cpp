
#include <window/Window.h>

#include <utils/log/Log.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <resources/Resources.h>

namespace prx {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	Window* Window::m_CurrentWindow = nullptr;

	Window::Window(std::string_view title, int width, int height, bool fullscreen)
		: m_Title(title), m_Width(width), m_Height(height), m_ClearColor(hpm::vec3(0.0, 0.0, 0.0)),
		m_FullScreen(fullscreen), m_ScrollOffsetX(0), m_ScrollOffsetY(0) {
		if (m_CurrentWindow != nullptr) {
			Log::message("WINDOW: Only one window can exist at the same time.", LOG_ERROR);
			ASSERT(m_CurrentWindow == nullptr);
		}

		if (!init())
			glfwTerminate();
		m_CurrentWindow = this;
	}


	bool Window::init() {
		
		// Initialize GLFW
		if (!glfwInit()) {
			prx::Log::message("Failed to init GLFW", prx::LOG_ERROR);
			return false;
		}

		//Getting monitor configuration
		m_Monitor = glfwGetPrimaryMonitor();

		if (m_FullScreen)
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Monitor, nullptr);
		else
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
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSwapInterval(1.0);

		glfwSetWindowUserPointer(m_Window, this);

		// Initialize keys events handling system
		memset(m_KeysCurrentState,  false, PARALLAX_INPUT_MAX_KEYS * sizeof(bool));
		memset(m_KeysPrevState,		false, PARALLAX_INPUT_MAX_KEYS * sizeof(bool));
		memset(m_KeysPressed,		false, PARALLAX_INPUT_MAX_KEYS * sizeof(bool));
		memset(m_KeysReleased,		false, PARALLAX_INPUT_MAX_KEYS * sizeof(bool));
		
		memset(m_MouseButtonsCurrentState,  false, PARALLAX_INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
		memset(m_MouseButtonsPrevState,		false, PARALLAX_INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
		memset(m_MouseButtonsPressed,		false, PARALLAX_INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
		memset(m_MouseButtonsReleased,		false, PARALLAX_INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));

		m_CursorX = m_Width / 2;
		m_CursorY = m_Width / 2;

		// Initialize GLEW
		if (glewInit() != GLEW_OK) {
			prx::Log::message("Failed to initialize GLEW", prx::LOG_ERROR);
			glfwTerminate();
			return false;
		}

		// Setting GL viewport
		GLCall(glViewport(0, 0, m_Width, m_Height));

		std::stringstream ss;
		ss << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		Log::message(ss.str(), LOG_INIT);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		return true;
	}
	Window::~Window() {
		glfwTerminate();
		m_CurrentWindow = nullptr;
	}

	bool Window::isClosed() const {
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::isKeyHeld(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			prx::Log::message("Invalid key number", prx::LOG_WARNING);
			return false;
		}
		return m_KeysCurrentState[key];
	}

	bool Window::isKeyPressed(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			prx::Log::message("Invalid key number", prx::LOG_WARNING);
			return false;
		}
		return m_KeysPressed[key];
	}

	bool Window::isKeyReleased(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			prx::Log::message("Invalid key number", prx::LOG_WARNING);
			return false;
		}
		return m_KeysReleased[key];
	}

	bool Window::isMouseButtonHeld(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message("Invalid mouse button number", prx::LOG_WARNING);
			return false;
		}
		return m_MouseButtonsCurrentState[button];
	}

	bool Window::isMouseButtonPressed(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message("Invalid mouse button number", prx::LOG_WARNING);
			return false;
		}
		return m_MouseButtonsPressed[button];
	}

	bool Window::isMouseButtonReleased(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message("Invalid mouse button number", prx::LOG_WARNING);
			return false;
		}
		return m_MouseButtonsReleased[button];
	}

	void Window::setClearColor(unsigned int color) {
		
		auto mask = static_cast<unsigned int>(0x000000ff);

		float r = (color & mask) / 255.0;
		float g = ((color >> 8)  & mask) / 255.0;
		float b = ((color >> 16) & mask) / 255.0;
		float a = ((color >> 24) & mask) / 255.0;
		
		glClearColor(r, g, b, a);
	}

	void Window::updateRender() {
		// Gorilla-audio update
		gau_manager_update(Resources::m_gaManager);

		// OpenGl update
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::updateInput() {
		// Key states update
		for (int i = 0; i < PARALLAX_INPUT_MAX_KEYS; i++) {
			m_KeysPressed[i] = m_KeysCurrentState[i] && !m_KeysPrevState[i];
			m_KeysReleased[i] = !m_KeysCurrentState[i] && m_KeysPrevState[i];
		}

		for (int i = 0; i < PARALLAX_INPUT_MAX_MOUSE_BUTTONS; i++) {
			m_MouseButtonsPressed[i] = m_MouseButtonsCurrentState[i] && !m_MouseButtonsPrevState[i];
			m_MouseButtonsReleased[i] = !m_MouseButtonsCurrentState[i] && m_MouseButtonsPrevState[i];
		}

		memcpy(m_KeysPrevState, m_KeysCurrentState, PARALLAX_INPUT_MAX_KEYS * sizeof(bool));
		memcpy(m_MouseButtonsPrevState, m_MouseButtonsCurrentState, PARALLAX_INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
	}

	void Window::clear(unsigned int flags) {
		if (flags & COLOR_BUFFER)
			glClear(GL_COLOR_BUFFER_BIT);
		if (flags & DEPTH_BUFFER)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Window::resize(unsigned width, unsigned height) {
		m_Width  = width;
		m_Height = height;
		glfwSetWindowSize(m_Window, width, height);
		GLCall(glViewport(0, 0, width, height));
	}

	void Window::enableFullScreen(bool fullscreen) {
		if (!m_FullScreen && fullscreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			m_FullScreen = true;
		}
		else if (m_FullScreen && !fullscreen) {
			glfwSetWindowMonitor(m_Window, NULL, 0, 0, m_Width, m_Height, 0);
			m_FullScreen = false;
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (key >= 0 && key < PARALLAX_INPUT_MAX_KEYS) {
			if (action == GLFW_PRESS)
				win->m_KeysCurrentState[key] = true;
			else if (action == GLFW_RELEASE)
				win->m_KeysCurrentState[key] = false;
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
		if (button >= 0 && button < PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			if (action == GLFW_PRESS)
				win->m_MouseButtonsCurrentState[button] = true;
			else if (action == GLFW_RELEASE)
				win->m_MouseButtonsCurrentState[button] = false;
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

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_Width = width;
		win->m_Height = height;
		GLCall(glViewport(0, 0, width, height));
	}
}

