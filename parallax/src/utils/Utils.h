#pragma once
#include <hypermath.h>
#include "../Common.h"

namespace prx {
	inline hpm::vec3 color_to_vec3(color_t color) noexcept {
		auto mask = static_cast<unsigned int>(0x000000ff);

		float r = (color & mask) / 255.0;
		float g = ((color >> 8)  & mask) / 255.0;
		float b = ((color >> 16) & mask) / 255.0;

		return hpm::vec3(r, g, b);
	}

	inline hpm::vec4 color_to_vec4(color_t color) noexcept {
		auto mask = static_cast<unsigned int>(0x000000ff);

		float r = (color & mask) / 255.0;
		float g = ((color >> 8)  & mask) / 255.0;
		float b = ((color >> 16) & mask) / 255.0;
		float a = ((color >> 24) & mask) / 255.0;

		return hpm::vec4(r, g, b, a);
	}

	inline color_t vec_to_color(hpm::vec3 color) noexcept {

		color_t r = color.r * 255.0;
		color_t g = color.g * 255.0;
		color_t b = color.b * 255.0;

		return 255 << 24 | b << 16 | g << 8 | r;
	};

	inline color_t vec_to_color(hpm::vec4 color) {

		color_t r = color.r * 255.0;
		color_t g = color.g * 255.0;
		color_t b = color.b * 255.0;
		color_t a = color.a * 255.0;

		return a << 24 | b << 16 | g << 8 | r;
	};
}
