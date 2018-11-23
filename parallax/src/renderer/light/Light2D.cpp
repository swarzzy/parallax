#include "Light2D.h"

namespace prx {
	Light2D::Light2D() 
		: m_Position(hpm::vec2(0.0f, 0.0f))
		, m_Depth(0.0f)
		, m_Color(0xffffffff)
		, m_Intensity(0.0f)
		, m_Radius(0.0f)
		, m_VolumeRadius(0.0f)
	{}

	Light2D::Light2D(hpm::vec2 position, float depth, unsigned color, float intensity, float radius) 
		: m_Position(position)
		, m_Depth(depth)
		, m_Color(color)
		, m_Intensity(intensity)
		, m_Radius(radius)
		, m_VolumeRadius(radius)
	{
		calcVolumeRadius();
	}

	Light2D::~Light2D() {
		
	}

	void Light2D::calcVolumeRadius() {
		// Converting uint color to vector
		auto mask = static_cast<unsigned int>(0x000000ff);
		float r = (m_Color & mask) / 255.0;
		float g = ((m_Color >> 8)  & mask) / 255.0;
		float b = ((m_Color >> 16) & mask) / 255.0;


		float maxComponent = std::fmaxf(std::fmaxf(r, g), b);
		//m_VolumeRadius = m_Radius * ((m_Radius * 0.8f) / m_Radius);
		m_VolumeRadius = m_Radius - (m_Radius * 0.05f);
	}
}
