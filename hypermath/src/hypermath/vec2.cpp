#include "vec2.h"

namespace hpm {
	vec2::vec2()
		: x(0.0f), y(0.0f) {}

	vec2::vec2(float x_, float y_)
		: x(x_), y(y_) {}

	vec2::vec2(float value) 
		: x(value), y(value) {}

	vec2::vec2(const vec2& vector) 
		: x(vector.x), y(vector.y){}

	vec2& vec2::add(const vec2& vector) {
		x += vector.x;
		y += vector.y;
		
		return *this;
	}
	vec2& vec2::subtract(const vec2& vector) {
		x -= vector.x;
		y -= vector.y;
		
		return *this;
	}
	vec2& vec2::multiply(const vec2& vector) {
		x *= vector.x;
		y *= vector.y;
		
		return *this;
	}
	vec2& vec2::divide(const vec2& vector) {
		x /= vector.x;
		y /= vector.y;
		
		return *this;
	}

	vec2& vec2::operator+=(const vec2& vector) {
		return add(vector);
	}

	vec2& vec2::operator-=(const vec2& vector) {
		return subtract(vector);
	}

	vec2& vec2::operator*=(const vec2& vector) {
		return multiply(vector);
	}

	vec2& vec2::operator/=(const vec2& vector) {
		return divide(vector);
	}

	bool vec2::operator==(const vec2& vector) {
		return (x == vector.x) && (y == vector.y);
	}

	bool vec2::operator!=(const vec2& vector) {
		return (x != vector.x) || (y != vector.y);
	}

	std::string vec2::toString() const {
		return std::string(std::to_string(x) + ' ' + std::to_string(y));
	}

	vec2& operator+(vec2 left, const vec2& right) {
		return left.add(right);
	}

	vec2& operator-(vec2 left, const vec2& right) {
		return left.subtract(right);
	}

	vec2& operator*(vec2 left, const vec2& right) {
		return left.multiply(right);
	}

	vec2& operator/(vec2 left, const vec2& right) {
		return left.divide(right);
	}
}
