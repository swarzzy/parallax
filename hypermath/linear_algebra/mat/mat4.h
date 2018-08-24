#pragma once
#ifndef _HYPERMATH_MAT4_H_
#define _HYPERMATH_MAT4_H_

#include "../vector.h"

namespace hpm {
	struct mat4 {
	public:
		// The order is column - major for OpenGL compability. 
		// Way to index elements: element index = column + raw * 4.
		// Columns and rows are indexed from zero.
		union {
			float elems[16];
			struct {
				vec4 columns[4];
			};
		};

		mat4();
		mat4(const mat4& mat);
		mat4(float diagonal);

		static mat4 identity();
		static mat4 ortho(float left, float right, float top, float bottom, float near, float far);
		static mat4 perspective(float fov,  float aspectRatio, float near, float far);
		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		mat4& multiply(const mat4& mat);
		friend mat4& operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& mat);

		vec3 multiply(const vec3& vector) const;
		friend vec3 operator*(const mat4& left, const vec3& right);

		vec4 multiply(const vec4& vector) const;
		friend vec4 operator*(const mat4& left, const vec4& right);


		bool operator==(const mat4& mat);
		bool operator!=(const mat4& mat);

		std::string toString() const;
	};
}
#endif
