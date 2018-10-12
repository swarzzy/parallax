
#pragma once
#ifndef _PARALLAX_UTILS_STRINGUTILS_H_
#define _PARALLAX_UTILS_STRINGUTILS_H_
#include <string>

namespace prx {
	enum class ShaderType;
}

namespace prx::utils {

	
	class StringUtils {
	public:
		StringUtils() = delete;

		template<typename T>
		inline static std::string toString(T arg) {
			using namespace std::string_literals;
			return " ["s + "toString: unsupported type: <"s + typeid(T).name() + ">]"s;
		}

		inline static std::string toString(const std::string& string) {
			return std::string(string);
		}

		inline static std::string toString(std::string_view string) {
			return std::string(string);
		}

		inline static std::string toString(char* str) {
			return std::string(str);
		}

		inline static std::string toString(char ch) {
			return std::to_string(ch);
		}

		inline static std::string toString(const char* str) {
			return std::string(str);
		}

		inline static std::string toString(int num) {
			return std::to_string(num);
		}

		inline static std::string toString(long num) {
			return std::to_string(num);
		}

		inline static std::string toString(long long num) {
			return std::to_string(num);
		}

		inline static std::string toString(unsigned int num) {
			return std::to_string(num);
		}

		inline static std::string toString(unsigned long int num) {
			return std::to_string(num);
		}

		inline static std::string toString(unsigned long long int num) {
			return std::to_string(num);
		}

		inline static std::string toString(float num) {
			return std::to_string(num);
		}

		inline static std::string toString(double num) {
			return std::to_string(num);
		}

		inline static std::string toString(long double num) {
			return std::to_string(num);
		}

		static std::string toString(ShaderType type);
	};
}
#endif