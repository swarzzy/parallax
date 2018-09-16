#pragma once
#ifndef _PARALLAX_GRAPHICS_FPS_COUNTER_H_
#define _PARALLAX_GRAPHICS_FPS_COUNTER_H_

#include "Label.h"
#include "../../utils/timing/SimpleTimer.h"
#include "../../Parallax.h"

namespace prx {
	class FPSCounter : public Label {
	private:
		const Application&	m_Application;
	public:
		FPSCounter(const Application& application);
		FPSCounter(hpm::vec3 position, unsigned int color, Font* font, const Application& application);
		void update();
	};
}
#endif
