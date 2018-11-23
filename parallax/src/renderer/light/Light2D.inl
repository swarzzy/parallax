#include "Light2D.h"
namespace prx {
	inline void Light2D::setPosition(hpm::vec2 position) {
		m_Position = position;
	}

	inline void Light2D::setPosition(float x, float y) {
		m_Position = hpm::vec2(x, y);
	}

	inline void Light2D::setDepth(float depth) {
		m_Depth = depth;
	}

	inline void Light2D::setColor(unsigned color) {
		m_Color = color;
	}

	inline void Light2D::setIntensity(float intensity) {
		m_Intensity = intensity;
	}

	inline void Light2D::setRadius(float radius) {
		m_Radius = radius;
		calcVolumeRadius();
	}

	inline const hpm::vec2& Light2D::getPosition() const {
		return m_Position;
	}

	inline float Light2D::getDepth() const {
		return m_Depth;
	}

	inline unsigned Light2D::getColor() const {
		return m_Color;
	}

	inline float Light2D::getIntensity() const {
		return m_Intensity;
	}

	inline float Light2D::getRadius() const {
		return m_Radius;
	}

	inline float Light2D::getVolumeRadius() const {
		return m_VolumeRadius;
	}
}
