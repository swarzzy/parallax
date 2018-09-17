#pragma once
#ifndef _PARALLAX_PARALLAX_H_
#define _PARALLAX_PARALLAX_H_

#include "window/Window.h"
#include "utils/timing/SimpleTimer.h";
#include "resources/Resources.h"
/*
 *		Basic application interface of parallax engine. It manages initialization and main game loop.
 *		You can write you game by overriding init, tick, update and render methods. Init method runs 
 *		once when application started. Tick method runs every second. Update runs 60 times per second.
 *		Render runs as fast as possible. Commonly you will update all game processes in update method
 *		and render things in render method. You should handle keyboard and other input events in render
 *		method because of specific realization. Parallax init method creates window and initializes all
 *		parallax systems (resources manager, audio system, logging system, etc.).
 */
namespace prx {
	class Application {
	private:
		Window*			m_Window;
		SimpleTimer*	m_Timer;
		unsigned int	m_FPS;
		unsigned int	m_UPS;
	
	protected:
		Application();
		virtual ~Application();
		
		Window* parallaxInit();
		Window* parallaxInit(std::string_view title, int width, int height,
			LOG_LEVEL logLevel, unsigned int clearColor);
		
		// Once at start
		virtual void init() = 0;
		// Once per second
		virtual void tick() {};
		// 60 times per second
		virtual void update() {};
		// As fast as possible
		virtual void render() = 0;


	private:
		void run();
	
	public:
		inline unsigned int getFPS() const { return m_FPS; }
		inline unsigned int getUPS() const { return m_UPS; }
		
		inline void start() { init(); run(); }
	};
}
#endif
