#pragma once
#ifndef _HYPERMATH_TRIG_FUNCTIONS_H_
#define _HYPERMATH_TRIG_FUNCTIONS_H_

namespace hpm {
	constexpr float Pi() noexcept {
		return 3.14159265358979323846f;
	}

	constexpr float degToRad(float degrees) noexcept {
		return degrees * (Pi() / 180.0f);
	}

	constexpr float radians(float degrees) noexcept {
		return degrees * (Pi() / 180.0f);
	}
}
#endif
