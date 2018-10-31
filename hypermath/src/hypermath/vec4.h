#pragma once

#ifndef _HYPERMATH_VEC4_H_
#define _HYPERMATH_VEC4_H_

#include <string>

namespace hpm {

	struct vec2;
	struct vec3;

	struct vec4 {
	public:
		union {
			float x;
			float r;
		};
		union {
			float y;
			float g;
		};
		union {
			float z;
			float b;
		};
		union {
			float w;
			float a;
		};

		vec4();
		vec4(float x_, float y_, float z_, float w_);
		explicit vec4(float value);
		vec4(const vec4& vector);
		vec4(const vec2& vector, float _z, float _w);
		vec4(const vec3& vector, float _w);

		vec4& add(const vec4& vector);
		vec4& subtract(const vec4& vector);
		vec4& multiply(const vec4& vector);
		vec4& divide(const vec4& vector);

		friend vec4& operator+(vec4 left, const vec4& right);
		friend vec4& operator-(vec4 left, const vec4& right);
		friend vec4& operator*(vec4 left, const vec4& right);
		friend vec4& operator/(vec4 left, const vec4& right);

		vec4& operator+=(const vec4& vector);
		vec4& operator-=(const vec4& vector);
		vec4& operator*=(const vec4& vector);
		vec4& operator/=(const vec4& vector);

		bool operator==(const vec4& vector);
		bool operator!=(const vec4& vector);

		std::string toString() const;
	};
}
#endif

