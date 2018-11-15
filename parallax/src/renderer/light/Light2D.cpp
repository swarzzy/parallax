#include "Light2D.h"

namespace prx {
	Light2D::Light2D() 
		: m_Position(hpm::vec2(0.0f, 0.0f))
		, m_Depth(0.0f)
		, m_Color(0xffffffff)
		, m_Brightness(0.0f)
		, m_Radius(0.0f)
	{
	}

	Light2D::Light2D(hpm::vec2 position, float depth, unsigned color, float brightness, float radius) 
		: m_Position(position)
		, m_Depth(depth)
		, m_Color(color)
		, m_Brightness(brightness)
		, m_Radius(radius)
	{
	}

	Light2D::~Light2D() {
		
	}
}
