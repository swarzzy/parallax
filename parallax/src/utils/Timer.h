#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

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
