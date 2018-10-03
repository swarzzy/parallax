#pragma once
#ifndef _PARALLAX_UTILS_STRINGUTILS_H_
#define _PARALLAX_UTILS_STRINGUTILS_H_
#include <string>

namespace prx::utils {
	class StringUtils {
	public:

		StringUtils() = delete;
		
		inline static std::string toString(const std::string string) {
			return string;
		}

		inline static std::string toString(const char* str) {
			return std::move(std::string(str));
		}

		inline static std::string toString(int num) {
			return std::move(std::to_string(num));
		}

		inline static std::string toString(unsigned int num) {
			return std::move(std::to_string(num));
		}

		inline static std::string toString(double num) {
			return std::move(std::to_string(num));
		}

		inline static std::string toString(float num) {
			return std::move(std::to_string(num));
		}

		inline static std::string toString(char ch) {
			return std::move(std::to_string(ch));
		}
	};
}

#endif