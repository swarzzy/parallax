#pragma once
#ifndef _PARALLAX_UTILS_SIMPLE_TIMER_H_
#define _PARALLAX_UTILS_SIMPLE_TIMER_H_

#include <chrono>

namespace prx {
	class SimpleTimer {
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
		
	public:
		SimpleTimer() 
			: m_StartTime(std::chrono::high_resolution_clock::now()) {};

		inline void reset() {
			m_StartTime = std::chrono::high_resolution_clock::now();
		}

		inline float elapsed() {
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::ratio<1, 1000>> timeElapsed = currentTime - m_StartTime;
			return timeElapsed.count();
		}
	};
}
#endif
