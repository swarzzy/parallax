#include "FPSCounter.h"

#include "../../resources/Resources.h"

namespace prx {

	FPSCounter::FPSCounter(hpm::vec3 position, unsigned int color, std::shared_ptr<Font> font)
		: Label("0", position, font, color),
		m_Timer(std::make_unique<SimpleTimer>()), m_FrameRate(0), m_FrameCounter(0) {}

	FPSCounter::FPSCounter() 
		: Label("0", hpm::vec3(10.0, 570.0, 0.0), Resources::loadFont(), 0xffffffff),
			m_Timer(std::make_unique<SimpleTimer>()), m_FrameRate(0), m_FrameCounter(0) {}

	void FPSCounter::update() {
		int elapsed = std::floor(m_Timer->elapsed());
		m_FrameCounter++;
		if (elapsed > 1000) {
			m_Timer->reset();
			m_FrameRate = m_FrameCounter;
			m_Text = std::to_string(m_FrameCounter);
			m_FrameCounter = 0;
		}
	}
}
