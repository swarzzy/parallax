
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

	Window::Window(std::string_view title, float width, float height, bool fullscreen)
		: m_Title(title), m_Width(width), m_Height(height), m_ClearColor(hpm::vec3(0.0, 0.0, 0.0)),
		m_FullScreen(fullscreen), m_ScrollOffsetX(0), m_ScrollOffsetY(0) {
		if (m_CurrentWindow != nullptr) {
			Log::message(LOG_LEVEL::LOG_ERROR, "WINDOW: Only one window can exist at the same time.");
			ASSERT(m_CurrentWindow == nullptr);
		}

		if (!init())
			glfwTerminate();
		m_CurrentWindow = this;
	}


	bool Window::init() {
		
		// Initialize GLFW
		if (!glfwInit()) {
			Log::message(LOG_LEVEL::LOG_FATAL, "Failed to init GLFW");
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
			prx::Log::message(LOG_LEVEL::LOG_FATAL, "Failed to create window");
			return false;
		}
		glfwMakeContextCurrent(m_Window);

		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSwapInterval(0);

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

		m_CursorX = m_Width / 2.0f;
		m_CursorY = m_Height / 2.0f;

		// Initialize GLEW
		if (glewInit() != GLEW_OK) {
			prx::Log::message(LOG_LEVEL::LOG_FATAL, "Failed to initialize GLEW");
			glfwTerminate();
			return false;
		}

		// Setting GL viewport
		GLCall(glViewport(0, 0, m_Width, m_Height));

		std::stringstream ss;
		ss << "OpenGL version: " << glGetString(GL_VERSION);
		Log::message(LOG_LEVEL::LOG_INFO, ss.str());

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		// TODO: Depth and blending modes
		//GLCall(glEnable(GL_DEPTH_TEST));

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
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid key number");
			return false;
		}
		return m_KeysCurrentState[key];
	}

	bool Window::isKeyPressed(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid key number");
			return false;
		}
		return m_KeysPressed[key];
	}

	bool Window::isKeyReleased(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid key number");
			return false;
		}
		return m_KeysReleased[key];
	}

	bool Window::isMouseButtonHeld(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid mouse button number");
			return false;
		}
		return m_MouseButtonsCurrentState[button];
	}

	bool Window::isMouseButtonPressed(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid mouse button number");
			return false;
		}
		return m_MouseButtonsPressed[button];
	}

	bool Window::isMouseButtonReleased(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid mouse button number");
			return false;
		}
		return m_MouseButtonsReleased[button];
	}

	void Window::setClearColor(unsigned int color) {
		
		auto mask = static_cast<unsigned int>(0x000000ff);

		float r = (color & mask) / 255.0f;
		float g = ((color >> 8)  & mask) / 255.0f;
		float b = ((color >> 16) & mask) / 255.0f;
		float a = ((color >> 24) & mask) / 255.0f;
		
		GLCall(glClearColor(r, g, b, a));
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
		// TODO: Join this two calls
	}

	void Window::resize(float width, float height) {
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
			if (action == PARALLAX_PRESS)
				win->m_KeysCurrentState[key] = true;
			else if (action == PARALLAX_RELEASE)
				win->m_KeysCurrentState[key] = false;
		}
		else {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid key number");
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_CursorX = static_cast<float>(xpos);
		win->m_CursorY = static_cast<float>(ypos);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (button >= 0 && button < PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			if (action == PARALLAX_PRESS)
				win->m_MouseButtonsCurrentState[button] = true;
			else if (action == PARALLAX_RELEASE)
				win->m_MouseButtonsCurrentState[button] = false;
		}
		else {
			prx::Log::message(LOG_LEVEL::LOG_WARN, "Invalid mouse key number");
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_ScrollOffsetX += static_cast<float>(xoffset);
		win->m_ScrollOffsetY += static_cast<float>(yoffset);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_Width = width;
		win->m_Height = height;
		GLCall(glViewport(0, 0, width, height));
	}
}

