#include "Window.h"

#include "../utils/log/Log.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../scene/Director.h"
#include "../audio/AudioEngine.h"
#ifdef PARALLAX_USING_IMGUI
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_glfw.h"
#endif

namespace prx {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void character_callback(GLFWwindow* window, unsigned int codepoint);

	Window* Window::m_CurrentWindow = nullptr;

	Window::Window(std::string_view title, unsigned width, unsigned height, bool fullscreen, bool resizeble)
		: m_Title(title), 
		  m_Width(width),
		  m_Height(height),
		  m_AspectRatioNum(0),
		  m_AspectRatioDenom(0),
		  m_ClearColor(hpm::vec3(0.0f, 0.0f, 0.0f)),
		  m_FullScreen(fullscreen), 
		  m_ScrollOffsetX(0), 
		  m_ScrollOffsetY(0),
		  m_Resizable(resizeble)
	{
		if (!init())
			glfwTerminate();
		m_CurrentWindow = this;
	}

	bool Window::init() {
		
		// Initialize GLFW
		if (!glfwInit()) {
			PRX_ERROR("PARALLAX: Failed to init GLFW");
			return false;
		}

		// Setting window hints
		glfwWindowHint(GLFW_RESIZABLE, m_Resizable);

		//Getting monitor configuration
		m_Monitor = glfwGetPrimaryMonitor();

		if (m_FullScreen)
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(),	m_Monitor, nullptr);
		else
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(),	nullptr, nullptr);

		if (!m_Window) {
			glfwTerminate();
			PRX_ERROR("PARALLAX: Failed to create window");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwMakeContextCurrent(m_Window);

		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetCharCallback(m_Window, character_callback);
		
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

		m_CursorX = static_cast<int>(m_Width) / 2.0f;
		m_CursorY = static_cast<int>(m_Height) / 2.0f;

		
		// Initializing GL3W
		if (gl3wInit()) {
			PRX_FATAL("Failed to initialize OpenGL");
			glfwTerminate();
			return false;
		}
		if (!gl3wIsSupported(3, 2)) {
			PRX_FATAL("OpenGL 3.2 not supported");
			glfwTerminate();
			return false;
		}

		PRX_INFO("\t PARALLAX ENGINE\n-> OPENGL VERSION: ", glGetString(GL_VERSION), "\n-> GLSL VERSION: ", glGetString(GL_SHADING_LANGUAGE_VERSION));

		return true;
	}
	Window::~Window() {
		// TODO: Destroy window propperly
		glfwTerminate();
		m_CurrentWindow = nullptr;
	}

	bool Window::isClosed() const {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::closeWindow() {
		glfwSetWindowShouldClose(m_Window, true);
	}

	bool Window::isKeyHeld(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			PRX_WARN("WINDOW: Invalid key number/n-> KEYNUM: ", key);
			return false;
		}
		return m_KeysCurrentState[key];
	}

	bool Window::isKeyPressed(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			PRX_WARN("WINDOW: Invalid key number/n-> KEYNUM: ", key);
			return false;
		}
		return m_KeysPressed[key];
	}

	bool Window::isKeyReleased(GLenum key) const {
		if (key >= PARALLAX_INPUT_MAX_KEYS) {
			PRX_WARN("WINDOW: Invalid key number/n-> KEYNUM: ", key);
			return false;
		}
		return m_KeysReleased[key];
	}

	bool Window::isMouseButtonHeld(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			PRX_WARN("WINDOW: Invalid mouse button number/n-> BTNNUM: ", button);
			return false;
		}
		return m_MouseButtonsCurrentState[button];
	}

	bool Window::isMouseButtonPressed(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			PRX_WARN("WINDOW: Invalid mouse button number/n-> BTNNUM: ", button);
			return false;
		}
		return m_MouseButtonsPressed[button];
	}

	bool Window::isMouseButtonReleased(GLenum button) const {
		if (button >= PARALLAX_INPUT_MAX_MOUSE_BUTTONS) {
			PRX_WARN("WINDOW: Invalid mouse button number/n-> BTNNUM: ", button);
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
		gau_manager_update(AudioEngine::getInstance()->getManager());

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

	void Window::resize(unsigned width, unsigned height) {
		m_Width  = width;
		m_Height = height;
		glfwSetWindowSize(m_Window, width, height);
		//GLCall(glViewport(0, 0, width, height));
	}

	void Window::setAspectRatio(unsigned num, unsigned denom) {
		if (num == 0 && denom == 0) {
			glfwSetWindowAspectRatio(m_Window, GLFW_DONT_CARE, GLFW_DONT_CARE);
			m_AspectRatioNum = 0;
			m_AspectRatioDenom = 0;
		}
		else {
			glfwSetWindowAspectRatio(m_Window, num, denom);
			m_AspectRatioNum = num;
			m_AspectRatioDenom = denom;
		}
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

#ifdef PARALLAX_USING_IMGUI
			// Calling ImGUI inside callbacks so ImGUI and parallax desn`t steal callbacks from each other
			ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mode);
#endif
		}
		else {
			PRX_WARN("WINDOW: Invalid key number/n-> KEYNUM: ", key);
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

#ifdef PARALLAX_USING_IMGUI
			// Calling ImGUI inside callbacks so ImGUI and parallax desn`t steal callbacks from each other
			ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
#endif
		}
		else {
			PRX_WARN("WINDOW: Invalid mouse button number/n-> BTNNUM: ", button);
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_ScrollOffsetX += static_cast<float>(xoffset);
		win->m_ScrollOffsetY += static_cast<float>(yoffset);

#ifdef PARALLAX_USING_IMGUI
		// Calling ImGUI inside callbacks so ImGUI and parallax desn`t steal callbacks from each other
		ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
#endif
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->m_Width = width;
		win->m_Height = height;
		if (Director::getInstance() != nullptr)
			Director::getInstance()->setViewport(hpm::vec2(static_cast<float>(width), static_cast<float>(height)));
	}

	void character_callback(GLFWwindow* window, unsigned int codepoint) {
#ifdef PARALLAX_USING_IMGUI
		// Calling ImGUI inside callbacks so ImGUI and parallax desn`t steal callbacks from each other
		ImGui_ImplGlfw_CharCallback(window, codepoint);
#endif
	}
}

