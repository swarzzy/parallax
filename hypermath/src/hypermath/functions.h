#pragma once
namespace hpm {	 
	// Map value t from range [a,b] to range [c,d]. If a = b of d = c returns 0
	inline float map(float t, float a, float b, float c, float d) noexcept {
		if (a == b || d == c) return 0.0f;
		return c + (d - c) / (b - a) * (t - a);
	}
}