#pragma once
#ifndef _HYPERMATH_TRIG_FUNCTIONS_H_
#define _HYPERMATH_TRIG_FUNCTIONS_H_

#define _USE_MATH_DEFINES

#include<math.h>

namespace hpm {
	inline constexpr float degToRad(float degrees) {
		return degrees * (static_cast<float>(M_PI) / 180.0f);
	}
}
#endif
