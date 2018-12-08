#include "Light2DBase.h"
#include "../../utils/Utils.h"

namespace prx {
	inline void Light2DBase::setPosition(hpm::vec2 position) {
		m_LightProperties.position = position;
		//m_LightVolumeProperties.position = position;
	}

	inline void Light2DBase::setPosition(float x, float y) {
		m_LightProperties.position = hpm::vec2(x, y);
		//m_LightVolumeProperties.position = hpm::vec2(x, y);
	}

	inline void Light2DBase::setDepth(float depth) {
		m_LightProperties.depth = depth;
	}

	inline void Light2DBase::setColor(color_t color) {
		m_LightProperties.color = color_to_vec3(color);
	}

	inline void Light2DBase::setIntensity(float intensity) {
		m_LightProperties.intensity = intensity;
	}

	inline void Light2DBase::setRadius(float radius) {
		m_LightProperties.radius = radius;
		m_LightVolumeProperties.radius = calcVolumeRadius();
	}

	inline const hpm::vec2& Light2DBase::getPosition() const {
		return m_LightProperties.position;
	}

	inline float Light2DBase::getDepth() const {
		return m_LightProperties.depth;
	}

	inline color_t Light2DBase::getColor() const {
		return vec_to_color(m_LightProperties.color);
	}

	inline const hpm::vec3& Light2DBase::getColor3f() const {
		return m_LightProperties.color;
	}

	inline float Light2DBase::getIntensity() const {
		return m_LightProperties.intensity;
	}

	inline const internal::DFR2D::DFR2DLightProperties& Light2DBase::getLightProperties() const {
		return m_LightProperties;
	}

	inline const internal::DFR2D::DFR2DLightVolumeProperties& Light2DBase::getLightVolumeProperties() const {
		return m_LightVolumeProperties;
	}

	inline float Light2DBase::getRadius() const {
		return m_LightProperties.radius;
	}

	inline float Light2DBase::getVolumeRadius() const {
		return m_LightVolumeProperties.radius;
	}
}
