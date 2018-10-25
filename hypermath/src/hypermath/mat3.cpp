#include "mat3.h"
#include "vec2.h"
#include "trigFunctions.h"
#include "mat4.h"

namespace hpm {

	mat3::mat3() noexcept  {
		memset(elems, 0, m_StorageSize * sizeof(float));
	}

	mat3::mat3(const mat3& mat) noexcept {
		memcpy(elems, mat.elems, m_StorageSize * sizeof(float));
	}

	mat3::mat3(float diagonal) noexcept {
		memset(elems, 0, m_StorageSize * sizeof(float));

		elems[0] = diagonal;
		elems[4] = diagonal;
		elems[8] = diagonal;
	}

	mat3::mat3(const mat4& mat) noexcept {
		elems[0] = mat.elems[0];
		elems[1] = mat.elems[1];
		elems[2] = mat.elems[2];

		elems[3] = mat.elems[4];
		elems[4] = mat.elems[5];
		elems[5] = mat.elems[6];

		elems[6] = mat.elems[8];
		elems[7] = mat.elems[9];
		elems[8] = mat.elems[10];
	}

	mat3 mat3::identity() noexcept {
		return mat3(1.0f);
	}

	mat3 mat3::translation(const vec2& translation) noexcept {
		mat3 result(1.0f);

		result.elems[0 + 2 * 3] = translation.x;
		result.elems[1 + 2 * 3] = translation.y;

		return result;
	}

	mat3 mat3::translation(float x, float y) noexcept {
		mat3 result(1.0f);

		result.elems[0 + 2 * 3] = x;
		result.elems[1 + 2 * 3] = y;

		return result;
	}

	mat3 mat3::rotation(float angle) noexcept {

		mat3 result(1.0f);

		float rad = degToRad(angle);
		float c = cos(rad);
		float s = sin(rad);

		result.elems[0 + 0 * 3] = c;
		result.elems[1 + 0 * 3] = -s;

		result.elems[0 + 1 * 3] = s;
		result.elems[1 + 1 * 3] = c;

		return result;
	}

	mat3 mat3::scale(const vec2& scale) noexcept {
		mat3 result(1.0f);

		result.elems[0 + 0 * 3] = scale.x;
		result.elems[1 + 1 * 3] = scale.y;

		return result;
	}

	mat3 mat3::scale(float x, float y) noexcept {
		mat3 result(1.0f);

		result.elems[0 + 0 * 3] = x;
		result.elems[1 + 1 * 3] = y;

		return result;
	}

	mat3& mat3::multiply(const mat3& mat) noexcept {

		float result[m_StorageSize];
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 3; e++) {
					sum += elems[x + e * 3] * mat.elems[e + y * 3];
				}
				result[x + y * 3] = sum;
			}
		}

		memcpy(elems, result, m_StorageSize * sizeof(float));

		return *this;
	}

	mat3& mat3::operator*=(const mat3& mat) noexcept {

		return multiply(mat);
	}

	vec2 mat3::multiply(const vec2& vector) const noexcept {

		return vec2(
			columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x,
			columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y
		);
	}


	vec3 mat3::multiply(const vec3& vector) const noexcept {

		return vec3(
			columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * vector.z + columns[3].x,
			columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * vector.z + columns[3].y,
			columns[0].z * vector.x + columns[1].z * vector.y + columns[2].z * vector.z + columns[3].z
		);
	}

	bool mat3::operator==(const mat3& mat) noexcept {
		for (int i = 0; i < m_StorageSize; i++)
			if (elems[i] != mat.elems[i])
				return false;
		return true;

	}

	bool mat3::operator!=(const mat3& mat) noexcept {
		for (int i = 0; i < m_StorageSize; i++)
			if (elems[i] != mat.elems[i])
				return true;
		return false;
	}

	std::string mat3::toString() const {
		std::string result;
		for (int i = 0; i < m_StorageSize; i++)
			result += std::to_string(elems[i]) + ' ';
		result.pop_back();
		return result;
	}

	mat3& operator*(mat3 left, const mat3& right) noexcept {

		return left.multiply(right);
	}

	vec3 operator*(const mat3& left, const vec3& right) noexcept {
		return left.multiply(right);
	}

	vec2 operator*(const mat3& left, const vec2& right) noexcept {
		return left.multiply(right);
	}
}
