#pragma once

#include "../utils/timing/SimpleTimer.h"
#include "../utils/log/Log.h"
#include "../shading/Shader.h"

namespace prx {
	class Application {
	private:
		static Application* m_CurrentApplication;

		SimpleTimer*	m_Timer;
		float			m_DeltaTime;
		float			m_LastFrameTime;
		unsigned int	m_FPS;
		unsigned int	m_UPS;

		float m_Time;

	protected:
		Application();
		virtual ~Application();


		void parallaxInit();
		void parallaxInit(std::string_view title, int width, int height, bool fullscreen,
			LOG_LEVEL logLevel, unsigned int clearColor);

		// Once at start
		virtual void init() = 0;
		// Once per second
		virtual void tick() {};
		// 60 times per second
		virtual void update() {};
		// As fast as possible
		virtual void render() = 0;
		// Once before application destructed
		virtual void destroy() {};


	private:
		void run();

	public:
		static inline Application* getInstance() { return m_CurrentApplication; }

		inline unsigned int getFPS() const { return m_FPS; }
		inline unsigned int getUPS() const { return m_UPS; }
		inline float		getDeltaTime() const { return m_DeltaTime; }
		inline float getTime() const { return m_Time; }

		inline void start() { init(); run(); }
	};
}
