#include <linear_algebra/mat/mat4.h>

#include <linear_algebra/vector.h>
#include <trigonometry/trig_functions.h>

namespace hpm {

	mat4::mat4() noexcept {
		memset(elems, 0, m_StorageSize * sizeof(float));
	}

	mat4::mat4(const mat4 & mat) noexcept {
		memcpy(elems, mat.elems, m_StorageSize * sizeof(float));
	}

	mat4::mat4(float diagonal) noexcept {
		memset(elems, 0, m_StorageSize * sizeof(float));
		
		elems[0]  = diagonal;
		elems[5]  = diagonal;
		elems[10] = diagonal;
		elems[15] = diagonal;
	}

	mat4 mat4::identity() noexcept {
		return mat4(1.0f);
	}

	mat4 mat4::ortho(float left, float right, float top, float bottom, float near, float far) {
		
		mat4 result;
		
		result.elems[0 + 0 * 4] = 2.0f / (right - left);
		result.elems[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elems[2 + 2 * 4] = -2.0f / (far - near);

		result.elems[0 + 3 * 4] = -(left + right) / (right - left);
		result.elems[1 + 3 * 4] = -(bottom + top) / (top - bottom);
		result.elems[2 + 3 * 4] = -(far + near)	 / (far - near);
		result.elems[3 + 3 * 4] = 1.0f;

		return result;
	}

	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
		
		mat4 result;
		
		float a = 1.0f / tan(degToRad(0.5f * fov));
		float b = a / aspectRatio;
		float c = (near + far) / (near - far);
		float d = (2.0f * near * far) / (near - far);

		result.elems[0 + 0 * 4] = b;
		result.elems[1 + 1 * 4] = a;
		result.elems[2 + 2 * 4] = c;
		result.elems[3 + 2 * 4] = -1.0f;
		result.elems[2 + 3 * 4] = d;

		return result;
	}

	mat4 mat4::translation(const vec3& translation) noexcept {
		mat4 result(1.0f);

		result.elems[0 + 3 * 4] = translation.x;
		result.elems[1 + 3 * 4] = translation.y;
		result.elems[2 + 3 * 4] = translation.z;

		return result;
	}

	mat4 mat4::translation(float x, float y, float z) noexcept {
		mat4 result(1.0f);

		result.elems[0 + 3 * 4] = x;
		result.elems[1 + 3 * 4] = y;
		result.elems[2 + 3 * 4] = z;

		return result;
	}

	mat4 mat4::rotation(float angle, const vec3& axis) noexcept{
		
		mat4 result(1.0f);

		float rad = degToRad(angle);
		float c = cos(rad);
		float s = sin(rad);
		float rc = 1.0f - c;

		// Old version
		result.elems[0 + 0 * 4] = axis.x * rc + c;
		result.elems[1 + 0 * 4] = axis.y * axis.x * rc + axis.z * s;
		result.elems[2 + 0 * 4] = axis.x * axis.z * rc - axis.y * s;

		result.elems[0 + 1 * 4] = axis.x * axis.y * rc - axis.z * s;
		result.elems[1 + 1 * 4] = axis.y * rc + c;
		result.elems[2 + 1 * 4] = axis.y * axis.z * rc + axis.x * s;

		result.elems[0 + 2 * 4] = axis.x * axis.z * rc + axis.y * s;
		result.elems[1 + 2 * 4] = axis.y * axis.z * rc - axis.x * s;
		result.elems[2 + 2 * 4] = axis.z * rc + c;

		/*result.elems[0 + 0 * 4] = axis.x * axis.x * rc + c;
		result.elems[1 + 0 * 4] = axis.y * axis.x * rc - axis.z * s;
		result.elems[2 + 0 * 4] = axis.x * axis.z * rc + axis.y * s;

		result.elems[0 + 1 * 4] = axis.x * axis.y * rc + axis.z * s;
		result.elems[1 + 1 * 4] = axis.y * axis.y * rc + c;
		result.elems[2 + 1 * 4] = axis.y * axis.z * rc - axis.x * s;

		result.elems[0 + 2 * 4] = axis.x * axis.z * rc - axis.y * s;
		result.elems[1 + 2 * 4] = axis.y * axis.z * rc + axis.x * s;
		result.elems[2 + 2 * 4] = axis.z * axis.z * rc + c;*/

		return result;
	}

	mat4 mat4::rotation(float angle, float x, float y, float z) noexcept{
		mat4 result(1.0f);

		float rad = degToRad(angle);
		float c = cos(rad);
		float s = sin(rad);
		float rc = 1.0f - c;

		// Old version
		result.elems[0 + 0 * 4] = x * rc + c;
		result.elems[1 + 0 * 4] = y * x * rc + z * s;
		result.elems[2 + 0 * 4] = x * z * rc - y * s;

		result.elems[0 + 1 * 4] = x * y * rc - z * s;
		result.elems[1 + 1 * 4] = y * rc + c;
		result.elems[2 + 1 * 4] = y * z * rc + x * s;

		result.elems[0 + 2 * 4] = x * z * rc + y * s;
		result.elems[1 + 2 * 4] = y * z * rc - x * s;
		result.elems[2 + 2 * 4] = z * rc + c;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) noexcept{
		mat4 result;

		result.elems[0 + 0 * 4] = scale.x;
		result.elems[1 + 1 * 4] = scale.y;
		result.elems[2 + 2 * 4] = scale.z;
		result.elems[3 + 3 * 4] = 1.0f;

		return result;
	}

	mat4 mat4::scale(float x, float y, float z) noexcept {
		mat4 result;

		result.elems[0 + 0 * 4] = x;
		result.elems[1 + 1 * 4] = y;
		result.elems[2 + 2 * 4] = z;
		result.elems[3 + 3 * 4] = 1.0f;

		return result;
	}

	mat4& mat4::multiply(const mat4& mat)noexcept  {
		
		float result[m_StorageSize];
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += elems[x + e * 4] * mat.elems[e + y * 4];
				}
				result[x + y * 4] = sum;
			}
		}

		memcpy(elems, result, m_StorageSize * sizeof(float));
		
		return *this;
	}

	mat4& mat4::operator*=(const mat4& mat) noexcept {
		
		return multiply(mat);
	}

	vec3 mat4::multiply(const vec3& vector) const noexcept {
		
		return vec3(
			columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * vector.z + columns[3].x,
			columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * vector.z + columns[3].y,
			columns[0].z * vector.x + columns[1].z * vector.y + columns[2].z * vector.z + columns[3].z
		);
	}


	vec4 mat4::multiply(const vec4& vector) const noexcept {
		
		return vec4(
			columns[0].x * vector.x + columns[1].x * vector.y + columns[2].x * vector.z + columns[3].x * vector.w,
			columns[0].y * vector.x + columns[1].y * vector.y + columns[2].y * vector.z + columns[3].y * vector.w,
			columns[0].z * vector.x + columns[1].z * vector.y + columns[2].z * vector.z + columns[3].z * vector.w,
			columns[0].w * vector.x + columns[1].w * vector.y + columns[2].w * vector.z + columns[3].w * vector.w
		);
	}

	bool mat4::operator==(const mat4& mat) noexcept {
		for (int i = 0; i < m_StorageSize; i++)
			if (elems[i] != mat.elems[i])
				return false;
		return true;

	}

	bool mat4::operator!=(const mat4& mat)noexcept {
		for (int i = 0; i < m_StorageSize; i++)
			if (elems[i] != mat.elems[i])
				return true;
		return false;
	}

	std::string mat4::toString() const {
		std::string result;
		for (int i = 0; i < m_StorageSize; i++)
			result += std::to_string(elems[i]) + ' ';
		result.pop_back();
		return result;
	}

	mat4& operator*(mat4 left, const mat4& right) noexcept {
		return left.multiply(right);
	}

	vec3 operator*(const mat4& left, const vec3& right) noexcept {
		return left.multiply(right);
	}

	vec4 operator*(const mat4& left, const vec4& right) noexcept {
		return left.multiply(right);
	}
}
