#pragma once
#ifndef _HYPERMATH_MAT4_H_
#define _HYPERMATH_MAT4_H_

#include <string>
#include "../vec/vec4.h"

namespace hpm {
	
	struct vec2;
	struct vec3;
	struct vec4;
	
	struct mat4 {
	private:
		inline static constexpr unsigned int m_StorageSize = 16;
	public:
		/*
		* The order is column - major for OpenGL compability. 
		* Way to index elements: element index = column + raw * 4.
		* Columns and rows are indexed from zero.
		*/
		union {
			float elems[16];
			struct {
				vec4 columns[4];
			};
		};

		mat4() noexcept;
		mat4(const mat4& mat) noexcept;
		explicit mat4(float diagonal) noexcept;

		static inline constexpr unsigned int storageSize() noexcept { return m_StorageSize; }

		static mat4 identity() noexcept;
		static mat4 ortho(float left, float right, float top, float bottom, float near, float far);
		static mat4 perspective(float fov,  float aspectRatio, float near, float far);
		static mat4 translation(const vec3& translation) noexcept;
		static mat4 translation(float x, float y, float z) noexcept;
		static mat4 rotation(float angle, const vec3& axis) noexcept;
		static mat4 rotation(float angle, float x, float y, float z) noexcept;
		static mat4 scale(const vec3& scale) noexcept;
		static mat4 scale(float x, float y, float z) noexcept;

		mat4& multiply(const mat4& mat) noexcept;
		friend mat4& operator*(mat4 left, const mat4& right) noexcept;
		mat4& operator*=(const mat4& mat) noexcept;

		vec3 multiply(const vec3& vector) const noexcept;
		friend vec3 operator*(const mat4& left, const vec3& right) noexcept;

		vec4 multiply(const vec4& vector) const noexcept;
		friend vec4 operator*(const mat4& left, const vec4& right) noexcept;


		bool operator==(const mat4& mat) noexcept;
		bool operator!=(const mat4& mat) noexcept;

		std::string toString() const;
	};
}
#endif
