#include "vec4.h"
#include "vec2.h"
#include "vec3.h"

namespace hpm {
	vec4::vec4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	vec4::vec4(float x_, float y_, float z_, float w_) 
		: x(x_), y(y_), z(z_), w(w_) {}

	vec4::vec4(float value) 
		: x(value), y(value), z(value), w(value){}

	vec4::vec4(const vec4& vector) 
		: x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	vec4::vec4(const vec2& vector, float _z, float _w) 
		: x(vector.x), y(vector.y), z(_z), w(_w) {}

	vec4::vec4(const vec3& vector, float _w) 
		: x(vector.x), y(vector.y), z(vector.z), w(_w) {}

	vec4& vec4::add(const vec4& vector) {
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;

		return *this;
	}
	vec4& vec4::subtract(const vec4& vector) {
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;

		return *this;
	}
	vec4& vec4::multiply(const vec4& vector) {
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;

		return *this;
	}
	vec4& vec4::divide(const vec4& vector) {
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;

		return *this;
	}

	vec4& vec4::operator+=(const vec4& vector) {
		return add(vector);
	}

	vec4& vec4::operator-=(const vec4& vector) {
		return subtract(vector);
	}

	vec4& vec4::operator*=(const vec4& vector) {
		return multiply(vector);
	}

	vec4& vec4::operator/=(const vec4& vector) {
		return divide(vector);
	}

	bool vec4::operator==(const vec4& vector) {
		return (x == vector.x) && (y == vector.y) &&
				(z == vector.z) && (w == vector.w);
	}

	bool vec4::operator!=(const vec4& vector) {
		return (x != vector.x) || (y != vector.y) ||
				(z != vector.z) || (w != vector.w);
	}

	std::string vec4::toString() const {
		return std::string(std::to_string(x) + ' ' + std::to_string(y) +
				' ' + std::to_string(z) + ' ' + std::to_string(w));
	}

	vec4& operator+(vec4 left, const vec4& right) {
		return left.add(right);
	}

	vec4& operator-(vec4 left, const vec4& right) {
		return left.subtract(right);
	}

	vec4& operator*(vec4 left, const vec4& right) {
		return left.multiply(right);
	}

	vec4& operator/(vec4 left, const vec4& right) {
		return left.divide(right);
	}
}
