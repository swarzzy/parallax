#pragma once
#ifndef _PARALLAX_UTILS_COLOR_FORMAT_CONVERTER_H_
#define _PARALLAX_UTILS_COLOR_FORMAT_CONVERTER_H_

#include <hypermath.h>

#include "../log/Log.h"

namespace prx {
	class ColorFormatConverter {
	public:

		static unsigned int vecColor(hpm::vec3 color) {

			unsigned int r = color.r * 255.0;
			unsigned int g = color.g * 255.0;
			unsigned int b = color.b * 255.0;

			return 255 << 24 | b << 16 | g << 8 | r;
		};

		//-----------------------------------------------------------------------------------------------------------

		static unsigned int vecColor(hpm::vec4 color) {

			unsigned int r = color.r * 255.0;
			unsigned int g = color.g * 255.0;
			unsigned int b = color.b * 255.0;
			unsigned int a = color.a * 255.0;

			return a << 24 | b << 16 | g << 8 | r;
		};
		//-----------------------------------------------------------------------------------------------------------

		static unsigned int rgb(unsigned int r, unsigned int g, unsigned int b) {
			if (r > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid r - channel value", LOG_WARNING);
				r = 255;
			}
			if (g > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid g - channel value", LOG_WARNING);
				g = 255;
			}
			if (b > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid b - channel value", LOG_WARNING);
				b = 255;
			}

			return 255 << 24 | b << 16 | g << 8 | r;
		}

		//-----------------------------------------------------------------------------------------------------------

		static unsigned int rgba(unsigned int r, unsigned int g, unsigned int b, float a) {
			if (r > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid r - channel value", LOG_WARNING);
				r = 255;
			}
			if (g > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid g - channel value", LOG_WARNING);
				g = 255;
			}
			if (b > 255) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid b - channel value", LOG_WARNING);
				b = 255;
			}
			if (a > 1.0) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid a - channel value", LOG_WARNING);
				a = 1.0;
			}

			unsigned int ca = a * 255.0;

			return ca << 24 | b << 16 | g << 8 | r;
		}

		//-----------------------------------------------------------------------------------------------------------

		unsigned int hex(std::string_view hex)
		{
			if (hex[0] != '#' || (hex.length() != 7 || hex.length() != 9)) {
				Log::message("COLOR_FORMAT_CONVERTER: Invalid hex color code", LOG_WARNING);
				return 255 << 24 | 255 << 16 | 255 << 8 | 255;
			}

			int r = std::stoi(static_cast<std::string>(hex.substr(1, 2)), nullptr, 16);
			int g = std::stoi(static_cast<std::string>(hex.substr(3, 2)), nullptr, 16);
			int b = std::stoi(static_cast<std::string>(hex.substr(5, 2)), nullptr, 16);
			int a = 255;
			if (hex.length() == 9)
				a = std::stoi(static_cast<std::string>(hex.substr(7, 2)), nullptr, 16);

			return a << 24 | b << 16 | g << 8 | r;;
		}

		//-----------------------------------------------------------------------------------------------------------

		static hpm::vec4 toVec(unsigned int color) {

			auto mask = static_cast<unsigned int>(0x000000ff);

			float r = (color & mask) / 255.0;
			float g = ((color >> 8)  & mask) / 255.0;
			float b = ((color >> 16) & mask) / 255.0;
			float a = ((color >> 24) & mask) / 255.0;

			return hpm::vec4(r, g, b, a);
		}
	};
}
#endif