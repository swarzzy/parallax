#pragma once

#ifndef _HYPERMATH_VEC2_H_
#define _HYPERMATH_VEC2_H_

#include <string>

namespace hpm {

	struct vec2 {
	public:
		union {
			float x;
			float r;
		};
		union {
			float y;
			float g;
		};

		vec2();
		vec2(float x_, float y_);
		explicit vec2(float value);
		vec2(const vec2& vector);
		
		vec2& add		(const vec2& vector);
		vec2& subtract	(const vec2& vector);
		vec2& multiply	(const vec2& vector);
		vec2& divide	(const vec2& vector);

		friend vec2& operator+(vec2 left, const vec2& right);
		friend vec2& operator-(vec2 left, const vec2& right);
		friend vec2& operator*(vec2 left, const vec2& right);
		friend vec2& operator/(vec2 left, const vec2& right);

		vec2& operator+=(const vec2& vector);
		vec2& operator-=(const vec2& vector);
		vec2& operator*=(const vec2& vector);
		vec2& operator/=(const vec2& vector);

		bool operator==(const vec2& vector);
		bool operator!=(const vec2& vector);

		std::string toString() const;
	};
}
#endif

