#pragma once
#ifndef _PARALLAX_GRAPHICS_FPS_COUNTER_H_
#define _PARALLAX_GRAPHICS_FPS_COUNTER_H_

#include "Label.h"
#include "../../utils/timing/SimpleTimer.h"

namespace prx {
	class FPSCounter : public Label {
	private:
		std::unique_ptr<SimpleTimer> m_Timer;
		unsigned int				 m_FrameRate;
		unsigned int				 m_FrameCounter;
	public:
		FPSCounter(hpm::vec3 position, unsigned int color, std::shared_ptr<Font> font);
		FPSCounter();
		void update();
	};
}
#endif
