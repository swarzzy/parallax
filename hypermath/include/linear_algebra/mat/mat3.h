#pragma once
#ifndef _HYPERMATH_MATRIX_MAT3_H_
#define _HYPERMATH_MATRIX_MAT3_H_

#include <string>
#include "../vec/vec3.h"

namespace hpm {

	struct vec2;
	struct vec3;
	struct vec4;

	struct mat4;

	struct mat3 {
	private:
		inline static constexpr unsigned int m_StorageSize = 9;
	public:
		// The order is column - major for OpenGL compability. 
		// Way to index elements: element index = column + raw * 4.
		// Columns and rows are indexed from zero.
		union {
			float elems[9];
			struct {
				vec3 columns[3];
			};
		};

		mat3() noexcept;
		mat3(const mat3& mat) noexcept;
		explicit mat3(float diagonal) noexcept;
		explicit mat3(const mat4& mat) noexcept;

		static inline constexpr unsigned int storageSize() noexcept { return m_StorageSize; }

		static mat3 identity() noexcept;
		static mat3 translation(const vec2& translation) noexcept;
		static mat3 translation(float x, float y) noexcept;
		static mat3 rotation(float angle) noexcept;
		static mat3 scale(const vec2& scale) noexcept;
		static mat3 scale(float x, float y) noexcept;

		mat3& multiply(const mat3& mat) noexcept;
		friend mat3& operator*(mat3 left, const mat3& right) noexcept;
		mat3& operator*=(const mat3& mat) noexcept;

		vec3 multiply(const vec3& vector) const noexcept;
		friend vec3 operator*(const mat3& left, const vec3& right) noexcept;

		vec2 multiply(const vec2& vector) const noexcept;
		friend vec2 operator*(const mat3& left, const vec2& right) noexcept;


		bool operator==(const mat3& mat) noexcept;
		bool operator!=(const mat3& mat) noexcept;

		std::string toString() const;
	};
}
#endif
