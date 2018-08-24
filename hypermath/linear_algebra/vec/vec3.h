#pragma once

#ifndef _HYPERMATH_VEC3_H_
#define _HYPERMATH_VEC3_H_

#include <string>

namespace hpm {

	struct vec2;

	struct vec3 {
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

		vec3();
		vec3(float _x, float _y, float _z);
		vec3(float value);
		vec3(const vec3& vector);
		vec3(const vec2& vector, float _z);

		vec3& add(const vec3& vector);
		vec3& subtract(const vec3& vector);
		vec3& multiply(const vec3& vector);
		vec3& divide(const vec3& vector);

		friend vec3& operator+(vec3 left, const vec3& right);
		friend vec3& operator-(vec3 left, const vec3& right);
		friend vec3& operator*(vec3 left, const vec3& right);
		friend vec3& operator/(vec3 left, const vec3& right);

		vec3& operator+=(const vec3& vector);
		vec3& operator-=(const vec3& vector);
		vec3& operator*=(const vec3& vector);
		vec3& operator/=(const vec3& vector);

		bool operator==(const vec3& vector);
		bool operator!=(const vec3& vector);

		std::string toString() const;
	};
}
#endif

