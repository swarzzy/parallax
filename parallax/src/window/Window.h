#pragma once
#ifndef _PARALLAX_WINDOW_WINDOW_H_
#define _PARALLAX_WINDOW_WINDOW_H_

#include "../ext/GL/glew.h"
#include "../ParallaxKeys.h"
#include <hypermath.h>
#include "../utils/Singleton.h"
#include "../Common.h"

namespace prx {

	const unsigned int PARALLAX_INPUT_MAX_KEYS = 1024;
	const unsigned int PARALLAX_INPUT_MAX_MOUSE_BUTTONS = 32;

	enum ClearFlags {
		COLOR_BUFFER = 1,		//0000
		DEPTH_BUFFER = 1 << 1	//0001
	};

	// Only one instance can exist at the same time.
	class Window final : public Singleton<Window> {
		PRX_DISALLOW_COPY_AND_MOVE(Window)
	private:

		static Window* m_CurrentWindow;
		
		std::string	 m_Title;
		unsigned	 m_Width;
		unsigned	 m_Height;
		unsigned	 m_AspectRatioNum;
		unsigned	 m_AspectRatioDenom;
		GLFWwindow*	 m_Window;
		GLFWmonitor* m_Monitor;
		hpm::vec3	 m_ClearColor;
		bool		 m_FullScreen;
		bool		 m_Resizable;

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
		
		Window(std::string_view title, unsigned width, unsigned height, bool fullscreen, bool resizeble = false);

	public:
		friend class Singleton<Window>;

		~Window();

		// Deprecated
		static inline const Window& getCurrentWindow() { return *m_CurrentWindow; };

		void updateRender();

		void updateInput();

		void clear(unsigned int flags);

		void resize(unsigned width, unsigned height);
		// Set aspect ratio of the window if both parameters passed as zero it set no aspect ratio
		void setAspectRatio(unsigned num, unsigned denom);

		void enableFullScreen(bool fullscreen);

		bool isClosed() const;
		void closeWindow();

		bool isKeyHeld		(unsigned key) const;
		bool isKeyPressed	(unsigned key) const;
		bool isKeyReleased	(unsigned key) const;

		bool isMouseButtonHeld		(unsigned button) const;
		bool isMouseButtonPressed	(unsigned button) const;
		bool isMouseButtonReleased	(unsigned button) const;

		inline GLFWwindow* getWindowPointer() { return m_Window; };
		
		inline unsigned getWidth() const  { return m_Width; };
		inline unsigned getHeight() const { return m_Height; };
		inline hpm::vec2 getSize() const { return hpm::vec2(static_cast<float>(m_Width), static_cast<float>(m_Height)); }
		
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
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
	};
}
#endif