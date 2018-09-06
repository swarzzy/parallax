#pragma once

#ifndef _PARALLAX_UTILS_TIMER_H_
#define _PARALLAX_UTILS_TIMER_H_

#ifdef PARALLAX_USE_DEPRECATED_FEATURES

#include<windows.h>

namespace prx {
	class Timer {
	private:
		LARGE_INTEGER m_Start;
		double m_Fequrency;
	public:
		Timer();
		void reset();
		float elapsed();
	};
}
#endif
#endif
