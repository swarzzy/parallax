#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_

// DEPRECATED
#ifdef PARALLAX_USE_DEPRECATED_FEATURES

#include <string_view>

#include "../../../hypermath/hypermath.h";

namespace prx {

	class Color {
	private:
		Color();

	public:
		static hpm::vec3 RGBtoGLVec(unsigned int r, unsigned int g, unsigned int b);
		static hpm::vec4 RGBAtoGLVec(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		static hpm::vec3 HEXtoGLVec(std::string_view hex);
	};

}
#endif
#endif
