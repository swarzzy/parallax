#include "Light2DBase.h"
#include "../../utils/Utils.h"

namespace prx {
	Light2DBase::Light2DBase() 
		: m_LightProperties({ color_to_vec3(0xffffffff), 0.0f, hpm::vec2(0.0f, 0.0f), 0.0f, 0.0f }) 
	{
		m_LightVolumeProperties.radius = 0.0f;
	}

	Light2DBase::Light2DBase(hpm::vec2 position, float depth, color_t color, float intensity, float radius) 
		: m_LightProperties({ color_to_vec3(color), radius, position, intensity, depth})
	{
		m_LightVolumeProperties.radius = calcVolumeRadius();
	}

	Light2DBase::~Light2DBase() {
		
	}

	float Light2DBase::calcVolumeRadius() {
		return m_LightProperties.radius - (m_LightProperties.radius * 0.05f);
	}
}
