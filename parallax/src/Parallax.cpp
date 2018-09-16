#include "Parallax.h"
namespace prx {
	Window* Application::parallaxInit(std::string_view title, int width, int height,
		LOG_LEVEL logLevel, unsigned int clearColor) {
		prx::Log::setLevel(logLevel);
		Resources::initAudioSystem();
		m_Window = new Window(title, width, height);
		m_Window->setClearColor(clearColor);
		Resources::init();
		return m_Window;
	}

	void Application::run() {
		m_Timer = new SimpleTimer();

		unsigned int updateTime = m_Timer->elapsed();
		unsigned int tickTime = m_Timer->elapsed();

		unsigned int frameCounter = 0;
		unsigned int updateCounter = 0;

		while (!m_Window->isClosed()) {
			m_Window->clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

			if (m_Timer->elapsed() - tickTime > 1000.0) {
				tickTime = m_Timer->elapsed();
				m_FPS = frameCounter;
				m_UPS = updateCounter;
				updateCounter = 0;
				frameCounter = 0;
				tick();
			}

			if (m_Timer->elapsed() - updateTime > 1000.0 / 60.0) {
				updateTime = m_Timer->elapsed();
				updateCounter++;
				update();
			}

			render();
			frameCounter++;
			m_Window->update();
		}
	}

	Application::Application() : m_FPS(0), m_UPS(0) {};

	Application::~Application() {
		Resources::terminate();
		delete m_Timer;
		delete m_Window;
	}

	Window* Application::parallaxInit() {
		prx::Log::setLevel(prx::LOG_DEFAULT);
		Resources::initAudioSystem();
		m_Window = new Window("parallax", 800, 600);
		m_Window->setClearColor(0xff000000);
		Resources::init();
		return m_Window;
	}
}
