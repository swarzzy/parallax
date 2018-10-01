#include <Parallax.h>

namespace prx {

	Application* Application::m_CurrentApplication = nullptr;
	
	Application::Application() 
	: m_DeltaTime(1.0), m_LastFrameTime(0.0), m_FPS(0), m_UPS(0), m_Time(0) {
		if (m_CurrentApplication != nullptr) {
			Log::message("APPLICATION: Only one application can exist at the same time.", LOG_ERROR);
			ASSERT(m_CurrentApplication == nullptr);
		}
		m_CurrentApplication = this;
	};
	
	Application::~Application() {
		Resources::terminate();
		delete m_Timer;
		delete m_Window;
		m_CurrentApplication = nullptr;
	}

	Window* Application::parallaxInit(std::string_view title, int width, int height, bool fullscreen,
		LOG_LEVEL logLevel, unsigned int clearColor) {
		prx::Log::setLevel(logLevel);
		Resources::initAudioSystem();
		m_Window = new Window(title, width, height, fullscreen);
		m_Window->setClearColor(clearColor);
		Resources::init();
		return m_Window;
	}

	void Application::run() {
		m_Timer = new SimpleTimer();
		m_Time = m_Timer->elapsed();

		float updateTime = m_Time;
		float tickTime = m_Time;
		float frameTime = m_Time;

		unsigned int framesPerTick = 0;
		unsigned int updateCounter = 0;

		while (!m_Window->isClosed()) {
			m_Time = m_Timer->elapsed();
			// TODO: maybe replace elapsed() with m_Time everywhere
			m_Window->clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

			if (m_Time - tickTime > 1000.0) {
				tickTime = m_Time;
				m_FPS = framesPerTick;
				m_UPS = updateCounter;
				updateCounter = 0;
				framesPerTick = 0;
				tick();
			}

			m_Time = m_Timer->elapsed();
			if (m_Time - updateTime > 1000.0 / 60.0) {
				updateTime = m_Time;
				updateCounter++;
				update();
				m_Window->updateInput();
			}

			m_Time = m_Timer->elapsed();
			frameTime = m_Time;
			m_DeltaTime = frameTime - m_LastFrameTime;
			m_LastFrameTime = frameTime;
			framesPerTick++;
			render();
			m_Window->updateRender();
		}
	}


	Window* Application::parallaxInit() {
		prx::Log::setLevel(prx::LOG_DEFAULT);
		Resources::initAudioSystem();
		m_Window = new Window("parallax", 800, 600, false);
		m_Window->setClearColor(0xff000000);
		Resources::init();
		return m_Window;
	}
}
