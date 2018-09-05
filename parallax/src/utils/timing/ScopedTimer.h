#pragma once
#ifndef _PARALLAX_UTILS_SCOPED_TIMER_H_
#define _PARALLAX_UTILS_SCOPED_TIMER_H_

#include <chrono>
#include <string>
#include <iostream>

#include "../log/Log.h"

namespace prx {
	class ScopedTimer {
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	
	public:
		ScopedTimer()
			: m_StartTime(std::chrono::high_resolution_clock::now()) {};
		
		~ScopedTimer() {
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float, std::ratio<1,1000>> timeElapsed = endTime - m_StartTime;
			std::cout << "[ SCOPED TIMER ] : Timer took: " << timeElapsed.count() << " ms" << std::endl;
		}
	};
}
#endif