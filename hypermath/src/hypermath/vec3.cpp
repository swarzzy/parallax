#include "vec3.h"
#include "vec2.h"

namespace hpm {
	vec3::vec3()
		: x(0.0f), y(0.0f), z(0.0f) {}

	vec3::vec3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {}

	vec3::vec3(float value) 
		: x(value), y(value), z(value) {}

	vec3::vec3(const vec3& vector) 
		: x(vector.x), y(vector.y), z(vector.z) {}

	vec3::vec3(const vec2& vector, float _z) 
		:x(vector.x), y(vector.y), z(_z) {}

	vec3& vec3::add(const vec3& vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}
	vec3& vec3::subtract(const vec3& vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}
	vec3& vec3::multiply(const vec3& vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;

		return *this;
	}
	vec3& vec3::divide(const vec3& vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;

		return *this;
	}

	vec3& vec3::operator+=(const vec3& vector) {
		return add(vector);
	}

	vec3& vec3::operator-=(const vec3& vector) {
		return subtract(vector);
	}

	vec3& vec3::operator*=(const vec3& vector) {
		return multiply(vector);
	}

	vec3& vec3::operator/=(const vec3& vector) {
		return divide(vector);
	}

	bool vec3::operator==(const vec3& vector) {
		return (x == vector.x) && (y == vector.y) && (z == vector.z);
	}

	bool vec3::operator!=(const vec3& vector) {
		return (x != vector.x) || (y != vector.y) || (z != vector.z);
	}

	std::string vec3::toString() const {
		return std::string(std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z));
	}

	vec3& operator+(vec3 left, const vec3& right) {
		return left.add(right);
	}

	vec3& operator-(vec3 left, const vec3& right) {
		return left.subtract(right);
	}

	vec3& operator*(vec3 left, const vec3& right) {
		return left.multiply(right);
	}

	vec3& operator/(vec3 left, const vec3& right) {
		return left.divide(right);
	}
}
