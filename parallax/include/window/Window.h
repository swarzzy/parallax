#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H

#include "../ext/GL/glew.h"
#include "../ext/GLFW/glfw3.h"

#include <hypermath.h>

namespace prx {

	const unsigned int PARALLAX_INPUT_MAX_KEYS = 1024;
	const unsigned int PARALLAX_INPUT_MAX_MOUSE_BUTTONS = 32;

	enum ClearFlags {
		COLOR_BUFFER = 1,		//0000
		DEPTH_BUFFER = 1 << 1	//0001
	};

	// Only one instance can exist at the same time.
	class Window {
	private:

		static Window* m_CurrentWindow;
		
		std::string	 m_Title;
		unsigned int m_Width, m_Height;
		GLFWwindow*	 m_Window;
		GLFWmonitor* m_Monitor;
		hpm::vec3	 m_ClearColor;
		bool		 m_FullScreen;

		bool m_KeysCurrentState	[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysPrevState	[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysPressed		[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysReleased		[PARALLAX_INPUT_MAX_KEYS];

		bool m_MouseButtonsCurrentState	[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsPrevState	[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsPressed		[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsReleased		[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];

		float m_CursorX, 
			  m_CursorY;
		
		float m_ScrollOffsetX, 
			  m_ScrollOffsetY;
		
	public:
		
		// Only one instance can exist at the same time.
		Window(std::string_view title, int width, int height, bool fullscreen);
		~Window();

		static inline const Window& getCurrentWindow() { return *m_CurrentWindow; };

		void updateRender();

		void updateInput();

		void clear(unsigned int flags);

		void resize(unsigned int width, unsigned int height);

		void enableFullScreen(bool fullscreen);

		bool isClosed() const;

		// TODO: button defines
		bool isKeyHeld		(GLenum key) const;
		bool isKeyPressed	(GLenum key) const;
		bool isKeyReleased	(GLenum key) const;

		bool isMouseButtonHeld		(GLenum button) const;
		bool isMouseButtonPressed	(GLenum button) const;
		bool isMouseButtonReleased	(GLenum button) const;

		inline GLFWwindow* getWindowPointer() { return m_Window; };
		
		inline unsigned int getWidth() const  { return m_Width; };
		inline unsigned int getHeight() const { return m_Height; };
		
		inline hpm::vec2 getCursorPos() const  { return hpm::vec2(m_CursorX, m_Height - m_CursorY); };
		inline double getScrollOffsetY() const { return m_ScrollOffsetY; };
		
		void setClearColor(unsigned int color);

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
}


#endif

