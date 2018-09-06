#include "Timer.h"

#ifdef PARALLAX_USE_DEPRECATED_FEATURES

namespace prx {

	Timer::Timer() {
		LARGE_INTEGER fequrency;
		QueryPerformanceFrequency(&fequrency);
		m_Fequrency = 1.0 / fequrency.QuadPart;
		QueryPerformanceCounter(&m_Start);

	}

	void Timer::reset() {
		QueryPerformanceCounter(&m_Start);
	}

	float Timer::elapsed() {
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned long long int cycles = current.QuadPart - m_Start.QuadPart;
		return static_cast<float>(cycles * m_Fequrency * 1000);
	}
}
#endif
