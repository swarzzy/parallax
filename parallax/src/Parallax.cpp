#include <Parallax.h>
#include <resources/ResourceManager.h>
#include <scene/Director.h>
#include <audio/AudioEngine.h>
#include <Fonts/FontManager.h>

namespace prx {

	Application* Application::m_CurrentApplication = nullptr;
	
	Application::Application() 
	: m_DeltaTime(1.0), 
	  m_LastFrameTime(0.0), 
	  m_FPS(0), 
	  m_UPS(0), 
	  m_Time(0) 
	{
		if (m_CurrentApplication != nullptr) {
			PRX_FATAL("APPLICATION: Only one application can exist at the same time.");
		}
		m_CurrentApplication = this;
	};
	
	Application::~Application() {
		//destroy();
		Director::destroy();
		AudioEngine::destroy();
		FontManager::destroy();
		ShaderManager::clear();
		ResourceManager::getInstance()->clean();
		ResourceManager::destroy();
		Log::exportToFile(LogLevel::LOG_INFO, "log.txt");
		delete m_Timer;
		Window::destroy();
		m_CurrentApplication = nullptr;
	}

	void Application::parallaxInit(std::string_view title, int width, int height, bool fullscreen,
		LogLevel logLevel, unsigned int clearColor) {
		Log::init();
		Log::setLevel(logLevel);
		Window::initialize(title, width, height, fullscreen);
		Window::getInstance()->setClearColor(clearColor);
		AudioEngine::initialize();
		ResourceManager::initialize();
		FontManager::initialize(1.0f);
		Director::initialize();
	}

	void Application::run() {
		auto window = Window::getInstance();
		
		m_Timer = new SimpleTimer();
		m_Time = m_Timer->elapsed();

		float updateTime = m_Time;
		float tickTime = m_Time;
		float frameTime = m_Time;

		unsigned int framesPerTick = 0;
		unsigned int updateCounter = 0;

		while (!window->isClosed()) {
			m_Time = m_Timer->elapsed();
			// TODO: maybe replace elapsed() with m_Time everywhere
			window->clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

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
				window->updateInput();
			}

			m_Time = m_Timer->elapsed();
			frameTime = m_Time;
			m_DeltaTime = frameTime - m_LastFrameTime;
			m_LastFrameTime = frameTime;
			framesPerTick++;
			render();
			window->updateRender();
		}
		destroy();
	}


	void Application::parallaxInit() {
		Log::init();
		Log::setLevel(LogLevel::LOG_INFO);
		Window::initialize("parallax", 800, 600, false);
		Window::getInstance()->setClearColor(0xff000000);
		AudioEngine::initialize();
		ResourceManager::initialize();
		FontManager::initialize(1.0f);
		Director::initialize();
	}
}
