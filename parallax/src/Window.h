#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H
#include <string_view>

#include <gl\glew.h>
#include <GLFW/glfw3.h>

#include "../../../hypermath/hypermath.h";

namespace prx {

	constexpr unsigned int PARALLAX_INPUT_MAX_KEYS = 1024;
	constexpr unsigned int PARALLAX_INPUT_MAX_MOUSE_BUTTONS = 32;

	enum ClearFlags {
		COLOR_BUFFER = 1,		//0000
		DEPTH_BUFFER = 1 << 1	//0001
	};

	class Window {
	private:
		std::string m_Title;
		unsigned int m_Width, m_Height;
		GLFWwindow* m_Window;
		hpm::vec3 m_ClearColor;

		bool m_KeysCurrentState[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysPrevState[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysPressed[PARALLAX_INPUT_MAX_KEYS];
		bool m_KeysReleased[PARALLAX_INPUT_MAX_KEYS];

		bool m_MouseButtonsCurrentState	[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsPrevState	[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsPressed		[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];
		bool m_MouseButtonsReleased		[PARALLAX_INPUT_MAX_MOUSE_BUTTONS];

		double m_CursorX, m_CursorY;
		double m_ScrollOffsetX, m_ScrollOffsetY;

	public:
		Window(std::string_view title, int width, int height);
		~Window();

		void update();
		void clear(unsigned int flags) const;

		bool isClosed() const;

		bool isKeyHeld		(GLenum key) const;
		bool isKeyPressed	(GLenum key) const;
		bool isKeyReleased	(GLenum key) const;

		bool isMouseButtonHeld		(GLenum button) const;
		bool isMouseButtonPressed	(GLenum button) const;
		bool isMouseButtonReleased	(GLenum button) const;

		inline GLFWwindow* getWindowPointer() const { return m_Window; };
		
		inline unsigned int getWidth() const { return m_Width; };
		inline unsigned int getHeight() const { return m_Height; };
		
		inline hpm::vec2 getCursorPos() const { return hpm::vec2(m_CursorX, m_CursorY); };
		inline double getScrollOffsetY() const { return m_ScrollOffsetY; };
		
		void setClearColor(unsigned int color);

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}


#endif

